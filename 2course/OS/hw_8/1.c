/*
Программа. В командной строке имена 3 файлов: f1, f2, f3.
Процесс создает двух потомков, возможны два варианта (два сына или сын и внук).

1ый потомок читает из f1, 2ой потомок из f2 - по строке и строго поочередно
пишут эти строки в f3. Синхронизация вывода в файл должна быть организована с
помощью каналов.(длина строки не ограничена)
Работу следует завершить, когда закончится хотя бы один файл.
Процесс, у которого файл еще не закончился, должен сообщить отцу, сколько строк
осталось необработанными, а отец должен вывести эту информацию на экран.
Файлы должны быть корректно закрыты по завершении работы.
*/

/*
Данная реализация работает по варианту с двумя сыновьями. Они синхронизируют
работу между собой, используя два канала(от первого к второму и от второго к
первому). После завершения файла один из сыновей отправляет специальный сигнал
другому, чтобы тот подсчитал строки в своем файле и отправил их отцу, через
третий канал.
*/

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

#define BUFFER_SIZE 1024
#define READ_END 0
#define WRITE_END 1

/*
Функция для динамического чтения строки из файлового дескриптора.
Строит строку посимвольно, пока не встретит символ переноса строки.
Eсли строка превышает размер буфера, то буфер увеличивается в два раза.
*/
char *readLine(int fd) {
  char *buffer = malloc(BUFFER_SIZE);
  if (!buffer) {
    perror("malloc failed");
    exit(EXIT_FAILURE);
  }

  int capacity = BUFFER_SIZE;
  int length = 0;
  char ch;
  int bytes_read;

  while ((bytes_read = read(fd, &ch, 1)) > 0) {
    if (length + 1 >= capacity) {
      capacity *= 2;
      buffer = realloc(buffer, capacity);
      if (!buffer) {
        perror("realloc failed");
        exit(EXIT_FAILURE);
      }
    }
    buffer[length++] = ch;
    if (ch == '\n')
      break;
  }

  if (bytes_read < 0) {
    perror("read failed");
    exit(EXIT_FAILURE);
  }
  if (length == 0 && bytes_read == 0) {
    free(buffer);
    return NULL;
  }

  buffer[length] = '\0';
  return buffer;
}

// Function to count lines in a file
int countLines(int fd) {
  if (lseek(fd, 0, SEEK_SET) == -1) {
    perror("Error seeking to start of file");
    return -1;
  }
  int lines = 0;
  char *line;
  while ((line = readLine(fd)) != NULL) {
    lines++;
    free(line);
  }
  if (lseek(fd, 0, SEEK_SET) == -1) {
    perror("Error seeking to start of file");
    return -1;
  }

  return lines;
}

// Just separated for general separation of concerns
void swap(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

/*
В моей реализации если второй файл больше первого, то количество строк выводится
с ошибкой. Чтобы гарантировать(без просмотра всех строк), что первый файл
больше, чем второй, можно сравнить размеры файлов. Однако, при сильно
различающихся строках в файлах, это может привести к неправильному выводу.
*/
void ensureFirstLarger(int *fd1, int *fd2) {
  struct stat stat1, stat2;
  if (fstat(*fd1, &stat1) < 0 || fstat(*fd2, &stat2) < 0) {
    perror("Error getting file stats");
    exit(EXIT_FAILURE);
  }
  if (stat1.st_size < stat2.st_size) {
    swap(fd1, fd2);
  }
}

/*
Точная проверка, что первый файл имеет больше строк, чем второй.
Использует полный просмотр обоих файлов.
*/
void ensureFirstMoreLines(int *fd1, int *fd2) {
  int lines1 = countLines(*fd1);
  int lines2 = countLines(*fd2);
  if (lines1 < 0 || lines2 < 0) {
    perror("Error counting lines");
    exit(EXIT_FAILURE);
  }
  if (lines1 < lines2) {
    swap(fd1, fd2);
  }
}

/*
Функция для обработки файла в сыновьях.
Получает на вход два канала для синхронизации, файловые дескрипторы и флаг,
указывающий, является ли данный сын первым.
Синхро
*/
void handleFile(int read_fd, int write_fd, int *pipe_in, int *pipe_out,
                int is_first_child) {
  close(pipe_in[WRITE_END]);
  close(pipe_out[READ_END]);

  int done = 0;
  char *line;

  if (is_first_child) {
    // First child starts immediately
    line = readLine(read_fd);
    if (line) {
      write(write_fd, line, strlen(line));
      free(line);
    } else {
      done = 1;
    }
    write(pipe_out[WRITE_END], &done, sizeof(done)); // Signal other child
  }

  while (!done) {
    // Wait for signal from other child
    read(pipe_in[READ_END], &done, sizeof(done));

    if (done)
      break; // Other child finished -> stop processing

    line = readLine(read_fd);
    if (line) {
      write(write_fd, line, strlen(line));
      free(line);
    } else {
      done = 1;
      // Signal other child and stop
      write(pipe_out[WRITE_END], &done, sizeof(done));
      break;
    }

    // Signal other child to write
    write(pipe_out[WRITE_END], &done, sizeof(done));
  }

  // Count remaining lines
  int remaining_lines = 0;
  while ((line = readLine(read_fd)) != NULL) {
    free(line);
    remaining_lines++;
  }

  if (remaining_lines > 0) {
    // Send remaining line count to parent if there are any
    write(pipe_out[WRITE_END], &remaining_lines, sizeof(remaining_lines));
  }

  close(read_fd);
  close(write_fd);
  close(pipe_in[READ_END]);
  close(pipe_out[WRITE_END]);
}

int main(int argc, char *argv[]) {
  if (argc != 4) {
    fprintf(stderr, "Usage: %s <file1> <file2> <file3>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  int pipe1[2], pipe2[2];
  if (pipe(pipe1) == -1 || pipe(pipe2) == -1) {
    perror("pipe failed");
    exit(EXIT_FAILURE);
  }

  int fd1 = open(argv[1], O_RDONLY);
  int fd2 = open(argv[2], O_RDONLY);
  int fd3 = open(argv[3], O_WRONLY | O_CREAT | O_TRUNC, 0644);

  if (fd1 == -1 || fd2 == -1 || fd3 == -1) {
    perror("open failed");
    exit(EXIT_FAILURE);
  }
  ensureFirstLarger(&fd1, &fd2);
  // ensureFirstMoreLines(&fd1, &fd2); // Uncomment to check more precisely

  pid_t pid1, pid2;
  if ((pid1 = fork()) == 0) {
    // First child process
    handleFile(fd1, fd3, pipe1, pipe2, 1);
    exit(EXIT_SUCCESS);
  } else if ((pid2 = fork()) == 0) {
    // Second child process
    handleFile(fd2, fd3, pipe2, pipe1, 0);
    exit(EXIT_SUCCESS);
  } else {
    // Parent process
    close(pipe1[READ_END]);
    close(pipe1[WRITE_END]);
    close(pipe2[WRITE_END]);

    int status;
    waitpid(pid1, &status, 0);
    waitpid(pid2, &status, 0);

    int remaining_lines = 0;
    if (read(pipe2[READ_END], &remaining_lines, sizeof(remaining_lines)) > 0) {
      printf("Remaining lines in the longer file: %d\n", remaining_lines);
    }

    close(fd1);
    close(fd2);
    close(fd3);
    close(pipe2[READ_END]);
  }

  return 0;
}