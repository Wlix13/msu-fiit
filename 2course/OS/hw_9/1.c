/*
В командной строке передается целое число N (задавать от 2 до 5, но код писать в
общем виде) и два числа — начальное и конечное. Реализовать игру в «ping-pong»
для N процессов на языке C.

Главный процесс порождает (N-1) потомков по любой схеме и начинает передачу
данных. Принимающий увеличивает число на 1 и передает дальше, и так по кругу до
тех пор, пока число не превысит заданный максимум. Каждый процесс выводит на
экран текущее число и свой pid.

Обмен данными через каналы (каждая пара процессов связана отдельным каналом).
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define READ_END 0
#define WRITE_END 1

void createPipe(int pipefd[2]) {
  if (pipe(pipefd) == -1) {
    perror("pipe");
    exit(EXIT_FAILURE);
  }
}

pid_t forkProcess() {
  pid_t pid = fork();
  if (pid == -1) {
    perror("fork");
    exit(EXIT_FAILURE);
  }
  return pid;
}

void waitForChildren(int N) {
  for (int i = 0; i < N - 1; i++)
    wait(NULL);
}

int main(int argc, char *argv[]) {
  if (argc != 4) {
    fprintf(stderr, "Usage: %s <N> <start> <end>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  int N, start, end;

  N = atoi(argv[1]);
  start = atoi(argv[2]);
  end = atoi(argv[3]);

  if (N < 2) {
    fprintf(stderr, "N must be greater than 1\n");
    exit(EXIT_FAILURE);
  }

  if (end < start) {
    fprintf(stderr, "End number must be greater than start\n");
    exit(EXIT_FAILURE);
  }

  int inPipe[2];
  int outPipe[2];
  int parentPipe[2];

  createPipe(outPipe);

  //  Redirect output to the parent pipe
  parentPipe[READ_END] = outPipe[READ_END];
  parentPipe[WRITE_END] = outPipe[WRITE_END];

  pid_t pid;
  for (int i = 0; i < N - 1; i++) {
    // Redirect input from the previous pipe
    inPipe[READ_END] = outPipe[READ_END];
    inPipe[WRITE_END] = outPipe[WRITE_END];

    createPipe(outPipe);

    pid = forkProcess();
    if (pid == 0) {
      close(parentPipe[WRITE_END]);
      if (i != 0)
        close(parentPipe[READ_END]);
      break;
    }

    if (i != 0) {
      close(inPipe[READ_END]);
      close(inPipe[WRITE_END]);
    }
  }

  if (pid > 0) {
    // Redirect input from the previous pipe
    inPipe[READ_END] = outPipe[READ_END];
    inPipe[WRITE_END] = outPipe[WRITE_END];

    // Redirect output to the parent pipe
    outPipe[READ_END] = parentPipe[READ_END];
    outPipe[WRITE_END] = parentPipe[WRITE_END];

    printf("PID: %d, %d\n", getpid(), start);
    write(outPipe[WRITE_END], &start, sizeof(int));
  }

  close(inPipe[WRITE_END]);
  close(outPipe[READ_END]);

  int num;
  while (read(inPipe[READ_END], &num, sizeof(int))) {
    printf("PID: %d, %d\n", getpid(), ++num);

    if (num >= end)
      break;

    write(outPipe[WRITE_END], &num, sizeof(int));
  }

  close(inPipe[READ_END]);
  close(outPipe[WRITE_END]);

  if (pid > 0)
    waitForChildren(N);

  return 0;
}