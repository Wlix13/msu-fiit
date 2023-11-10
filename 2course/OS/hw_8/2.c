/*
Напишите программу. Родитель создает сына, тот — внука, а тот — правнука.
Правнук передает в канал текущее время, полученное с помощью системного вызова
time, в бинарном виде (тип time_t).

Отец, сын и внук считывают время из канала. Процесс-отец выводит на экран строку
"Y:????", где ???? заменяются на текущий год, сын — "M:??", где ?? заменяются на
текущий месяц в году (от 1 до 12), число всегда выводится с двумя знаками, внук
— "D:??", где ?? заменяются на номер дня в месяце, всегда выводящееся с двумя
знаками.

Внук должен вывести число первым, сын — вторым, а отец — третьим. Записывать в
канал разрешается только правнуку. Родитель должен дождаться завершения всех
процессов и завершиться сам с кодом 0.

Пример вывода:

D:01
M:11
Y:2023
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#define READ_END 0
#define WRITE_END 1

int main() {
  int fd[2];
  pid_t pid;
  time_t current_time;
  struct tm *time_info;

  if (pipe(fd) == -1) {
    perror("pipe");
    exit(EXIT_FAILURE);
  }

  // Fork the first child (Son)
  pid = fork();
  if (pid == -1) {
    perror("son fork");
    exit(EXIT_FAILURE);
  } else if (pid == 0) {
    // Fork the second child (GrandSon)
    pid = fork();
    if (pid == -1) {
      perror("grandson fork");
      exit(EXIT_FAILURE);
    } else if (pid == 0) {
      // Fork the third child (Great-GrandSon)
      pid = fork();
      if (pid == -1) {
        perror("great-grandson fork");
        exit(EXIT_FAILURE);
      } else if (pid == 0) {
        // Great-Grandson process
        close(fd[READ_END]);

        // Get the current time
        time(&current_time);

        // Write the current time to the pipe 3 times (for each parent)
        write(fd[WRITE_END], &current_time, sizeof(current_time));
        write(fd[WRITE_END], &current_time, sizeof(current_time));
        write(fd[WRITE_END], &current_time, sizeof(current_time));
        close(fd[WRITE_END]);

        exit(EXIT_SUCCESS);
      } else {
        // Grandson process
        wait(NULL); // Wait for Great-GrandSon

        close(fd[WRITE_END]);
        read(fd[READ_END], &current_time, sizeof(current_time));
        time_info = localtime(&current_time);

        printf("D:%02d\n", time_info->tm_mday);

        exit(EXIT_SUCCESS);
      }
    } else {
      // Son process
      wait(NULL); // Wait for GrandSon

      close(fd[WRITE_END]);
      read(fd[READ_END], &current_time, sizeof(current_time));
      time_info = localtime(&current_time);

      printf("M:%02d\n", time_info->tm_mon + 1);

      exit(EXIT_SUCCESS);
    }
  } else {
    // Parent process
    wait(NULL); // Wait for Son

    close(fd[WRITE_END]);
    read(fd[READ_END], &current_time, sizeof(current_time));
    time_info = localtime(&current_time);

    printf("Y:%d\n", time_info->tm_year + 1900);

    close(fd[READ_END]);
  }

  return 0;
}
