/*
Написать программу, которая в командной строке получает целое число N —
начальное значение счетчика. После запуска процесс находится в режиме ожидания
поступления сигнала. При получении сигнала SIGTSTP (Ctrl-Z) счетчик
увеличивается на 3, при получении сигнала SIGINT (Ctrl-C) счетчик уменьшается
на 4. При получении каждого сигнала на экран выводится номер и название сигнала,
а также значение счетчика после его изменения. Работа программы прекращается,
когда счетчик станет меньше нуля.
*/

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int counter = 0;

void sigtstp_handler(int signum) {
  counter += 3;
  printf("SIGTSTP: %d\n", counter);
}

void sigint_handler(int signum) {
  counter -= 4;
  printf("SIGINT: %d\n", counter);
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Usage: %s <N>\n", argv[0]);
    return 1;
  }

  int N = atoi(argv[1]);
  counter = N;

  signal(SIGTSTP, sigtstp_handler);
  signal(SIGINT, sigint_handler);

  while (counter > 0) {
    sleep(1);
  }

  return 0;
}