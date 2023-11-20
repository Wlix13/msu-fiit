/*
Дополнить программу так, чтобы отец и сын поочередно читали по слову из файла
(имя задать в командной строке). Длина строки в файле ограничена MAXLEN. Работу
с файлом следует осуществлять с помощью системных функций. Вывод должен стать
таким: Father слово1 Son слово2 Father словоЗ Son слово4 Father слово5 Son
словоб и т.д. и продолжаться в течение 1 секунды или до конца файла.
*/

#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAXLEN 100

volatile pid_t pid;
volatile int fd;

char *GetWordFromFile() {
  char *word = (char *)malloc(MAXLEN * sizeof(char));
  int i = 0;
  char c;
  while (read(fd, &c, 1) > 0) {
    if (c == ' ' || c == '\n') {
      word[i] = '\0';
      return word;
    }
    word[i++] = c;
  }
  word[i] = '\0';
  return word;
}

void ChildPrintHandler(int s) {
  char *word = GetWordFromFile();
  if (strlen(word) == 0)
    kill(getppid(), SIGALRM);
  else {
    printf("Son  %s\n", word);
    free(word);
    kill(getppid(), SIGUSR1);
  }
}

void ParentPrintHandler(int s) {
  char *word = GetWordFromFile();
  if (strlen(word) == 0)
    kill(pid, SIGALRM);
  else {
    printf("Father %s\n", word);
    free(word);
    kill(pid, SIGUSR1);
  }
}

void ChildAlarmHandler(int s) {
  exit(EXIT_SUCCESS); //
}

void ParentAlarmHandler(int s) {
  signal(SIGINT, SIG_DFL); // Reset the interrupt signal to default
  kill(pid, SIGKILL);      // Kill the child process
  waitpid(pid, NULL, 0);
  printf("\n");
  while (1) {
    printf("Father \n");
    sleep(1);
  }
}

int main(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  fd = open(argv[1], O_RDONLY);
  if (fd == -1) {
    perror("open");
    exit(EXIT_FAILURE);
  }

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