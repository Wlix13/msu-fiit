/*
5 Возникает ли процесс «зомби» при завершении порожденного процесса, если сигнал
SIGCHLD родительским процессом:
а) перехватывается, б) не перехватывается, в) игнорируется.
*/

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

void child_exit_handler(int sig) {
  while (waitpid(-1, NULL, WNOHANG) > 0)
    ;
}

void signal_handler(int sig) { printf("Signal %d handled\n", sig); }

int main() {
  // signal(SIGCHLD, signal_handler);
  // signal(SIGCHLD, child_exit_handler);
  signal(SIGCHLD, SIG_IGN);

  pid_t pid = fork();

  if (pid == 0) {
    // Child
    exit(0);
  } else {
    // Parent
    sleep(1);
    system("ps a");
  }

  return 0;
}
