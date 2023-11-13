/*
4 Возобновляет ли работу функция wait(), если во время ожидания
пришел сигнал, или она завершается с ошибкой?
*/

#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

void signal_handler(int sig) { printf("Signal %d handled\n", sig); }

int main() {
  signal(SIGINT, signal_handler);
  if (fork() == 0) {
    sleep(5); // Child sleeps
    printf("Child exiting\n");
    return 0;
  }
  int status;
  if (wait(&status) == -1 && errno == EINTR) {
    printf("`wait()` interrupted by signal\n");
  }
  system("ps a");
  return 0;
}
