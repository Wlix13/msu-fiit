/*
3 При посылке сигнала всей своей группе получает ли этот сигнал тот процесс,
который его отправляет?
*/

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

void signal_handler(int sig) {
  printf("Process %d got signal %d\n", getpid(), sig);
  exit(0);
}

int main() {
  signal(SIGTERM, signal_handler);

  printf("Parent PID: %d\n", getpid());

  pid_t pid;
  for (int i = 0; i < 3; i++) {
    pid = fork();
    if (pid == 0) {
      // Child
      printf("Child PID: %d\n", getpid());
      pause();
      exit(0);
    }
  }

  sleep(1);
  printf("Sending SIGTERM to group...\n");
  kill(0, SIGTERM);

  while (wait(NULL) > 0)
    ;

  return 0;
}
