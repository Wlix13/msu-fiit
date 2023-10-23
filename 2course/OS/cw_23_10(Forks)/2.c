/*
Написать две программы р) и 5):
В командной строке передаются имена 2-ух исполняемых файлов, для каждого по 1
параметру, а также символ р или s — определяет способ запуска. Использовать
программу из п.1.
р) Запустить эти программы с использованием передачи данных в виде списка на
параллельное исполнение (т.е. работают одновременно).
s) Запустить эти программы (переданные в командной строке) с использованием
векторной передачи данных на последовательное исполнение (работают строго одна
после другой).
Определить, как завершились запущенные программы, вывести эту
информацию на экран (успешно ли (т.е. по exit), что вернул exit, по какому
сигналу). По окончании работы не должно остаться процессов «зомби».
*/

#include "fcntl.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void print_status(int status) {
  if (WIFEXITED(status)) {
    printf("Exit status: %d\n", WEXITSTATUS(status));
  } else if (WIFSIGNALED(status)) {
    printf("Exit by signal: %d\n", WTERMSIG(status));
  }
}

void parallel(char *prog1, char *prog2, char *arg1, char *arg2) {
  int status;
  pid_t pid1, pid2;

  if ((pid1 = fork()) == 0) {
    execlp(prog1, prog1, arg1, NULL);
    perror(prog1);
    exit(1);
  } else if ((pid2 = fork()) == 0) {
    execlp(prog2, prog2, arg2, NULL);
    perror(prog2);
    exit(1);
  }

  waitpid(pid1, &status, 0);
  print_status(status);
  waitpid(pid2, &status, 0);
  print_status(status);
}

void serial(char *prog1, char *prog2, char *arg1, char *arg2) {
  int status;
  pid_t pid1, pid2;

  if ((pid1 = fork()) == 0) {
    execlp(prog1, prog1, arg1, NULL);
    perror(prog1);
    exit(1);
  }

  waitpid(pid1, &status, 0);
  print_status(status);

  if ((pid2 = fork()) == 0) {
    execlp(prog2, prog2, arg2, NULL);
    perror(prog2);
    exit(1);
  }

  waitpid(pid2, &status, 0);
  print_status(status);
}

int main(int argc, char *agrv[]) {
  if (argc != 6) {
    printf("Usage: %s <prog1> <prog2> <arg1> <arg2> <mode>\n", agrv[0]);
    exit(1);
  }
  char mode = agrv[5][0];

  if (mode == 'p')
    parallel(agrv[1], agrv[2], agrv[3], agrv[4]);
  else if (mode == 's')
    serial(agrv[1], agrv[2], agrv[3], agrv[4]);
  else
    printf("Wrong mode: %c\n", mode);

  return 0;
}