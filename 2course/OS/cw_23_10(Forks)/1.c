/*
Написать программу, которая получает в командной строке число N и выводит на
экран свой pid N раз.
- Сделать 3 варианта завершения программы — exit (0), exit(1), abort() и создать
3 исполняемых файла соответственно. Полученные исполняемые файлы будут
использованы для тестирования следующей задачи.
*/

#include "fcntl.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int i, n;
  pid_t pid = getpid();

  if (argc != 2) {
    printf("Usage: %s <n>\n", argv[0]);
    exit(1);
  }

  n = atoi(argv[1]);

  for (i = 0; i < n; i++) {
    printf("%d\n", pid);
  }

  // exit(0);
  // exit(1);
  abort();
  return 0;
}