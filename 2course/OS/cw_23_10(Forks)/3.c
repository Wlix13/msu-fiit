/*
В командной строке передаются имена 2-ух исполняемых файлов, для каждого задано
по 1 параметру, также передается имя файла для вывода. Написать программу,
которая реализует запуск этих команд в виде конвейера, перенаправляя вывод в
заданный файл.
Тестировать можно так: /a.out cat file cat -n frez
*/
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  if (argc != 6) {
    fprintf(stderr, "Usage: %s <exec1> <arg1> <exec2> <arg2> <outfile>\n",
            argv[0]);
    exit(1);
  }

  int fd[2];
  if (pipe(fd) == -1) {
    perror("pipe");
    exit(1);
  }

  if (fork() == 0) {
    close(fd[0]); // Close unused read
    dup2(fd[1], 1);
    close(fd[1]);
    execlp(argv[1], argv[1], argv[2], NULL);
    perror("execlp");
    exit(1);
  }

  if (fork() == 0) {
    close(fd[1]); // Close unused write
    dup2(fd[0], 0);
    close(fd[0]);

    // Redirect stdout to file
    int fdOut = open(argv[5], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    dup2(fdOut, 1);
    close(fdOut);

    execlp(argv[3], argv[3], argv[4], NULL);
    perror("execlp");
    exit(1);
  }

  close(fd[0]);
  close(fd[1]);

  wait(NULL);
  wait(NULL);

  return 0;
}
