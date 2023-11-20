/*
Написать программу. Работают два процесса: отец и сын.
Отец выводит на экран "Father", а сын - "Son".
Вывод строго чередуется и должен происходить многократно (Father Son Father Son
Father Son и т.д.) в течение 2.
Через 2 секунды сын завершает работу, а отец продолжает выводить "Father", но с
интервалом в 1 секунду. Завершается отец по Ctrl-С.
Не должно остаться процессов-зомби.
*/

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

volatile pid_t pid;

void ChildPrintHandler(int s) {
  printf("Son \n");
  kill(getppid(), SIGUSR1);
}

void ParentPrintHandler(int s) {
  printf("Father \n");
  kill(pid, SIGUSR1);
}

void ChildAlarmHandler(int s) {
  exit(EXIT_SUCCESS); //
}

void ParentAlarmHandler(int s) {
  signal(SIGINT, SIG_DFL); // Reset the interrupt signal to default
  kill(pid, SIGKILL);      // Kill the child process
  waitpid(pid, NULL, 0);

  printf("\n");
  system("ps a"); // To show that there are no zombie processes

  while (1) {
    printf("Father \n");
    sleep(1);
  }
}

int main(int argc, char **argv) {
  pid = fork();
  if (pid == -1) {
    perror("fork");
    exit(EXIT_FAILURE);
  }

  if (pid == 0) {
    // Child process
    signal(SIGALRM, ChildAlarmHandler);
    signal(SIGUSR1, ChildPrintHandler);
    alarm(2);
    kill(getppid(), SIGUSR1); // Send signal to parent process
    for (;;)
      pause();
  } else {
    // Parent process
    signal(SIGALRM, ParentAlarmHandler);
    signal(SIGUSR1, ParentPrintHandler);
    alarm(2);
    for (;;)
      pause();
  }
}