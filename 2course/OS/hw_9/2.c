/*
В командной строке передается целое число N (задавать от 2 до 5, но код писать в
общем виде) и два числа — начальное и конечное. Реализовать игру в «ping-pong»
для N процессов на языке C.

Главный процесс порождает (N-1) потомков по любой схеме и начинает передачу
данных. Принимающий увеличивает число на 1 и передает дальше, и так по кругу до
тех пор, пока число не превысит заданный максимум. Каждый процесс выводит на
экран текущее число и свой pid.

Обмен данными через один канал. Синхронизация обращений к каналу должна быть
организована с помощью сигналов.
*/

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define READ_END 0
#define WRITE_END 1

int pipefd[2];
int current_process = 0;
int N, start, end;
pid_t *pids;

void createPipe() {
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

void handler(int signum) {
  int num;
  read(pipefd[READ_END], &num, sizeof(int));
  printf("PID: %d, Number: %d\n", getpid(), ++num);
  if (num >= end) {
    for (int i = 0; i < N - 1; i++) {
      kill(pids[i], SIGTERM);
    }
    kill(getppid(), SIGTERM);
  } else {
    write(pipefd[WRITE_END], &num, sizeof(int));
    kill(pids[current_process % (N - 1)], SIGUSR1);
    current_process++;
  }
}

void handlerTerm(int signum) {
  close(pipefd[READ_END]);
  close(pipefd[WRITE_END]);
  free(pids);
  exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[]) {
  if (argc != 4) {
    fprintf(stderr, "Usage: %s <N> <start> <end>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

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

  createPipe();

  signal(SIGUSR1, handler);
  signal(SIGTERM, handlerTerm);

  pids = calloc((N - 1), sizeof(pid_t));
  for (int i = 0; i < N - 1; i++) {
    pids[i] = forkProcess();
    if (pids[i] == 0) {
      while (1)
        pause();
      exit(EXIT_SUCCESS);
    }
  }

  // Parent
  printf("PID: %d, Number: %d\n", getpid(), start);
  write(pipefd[WRITE_END], &start, sizeof(int));
  kill(pids[current_process % (N - 1)], SIGUSR1);
  current_process++;
  pause();

  return 0;
}