/*
Программе в аргументах командной строки передается имя произвольного файла.
Главный процесс создает двух сыновей.
Второй сын пересылает первому сыну содержимое указанного файла, а первый сын
выводит полученные данные на стандартный поток вывода.
Для пересылки файла используется механизм сигналов: файл пересылается побитно,
для пересылки бита 0 второй сын отправляет первому сыну сигнал SIGUSR1, а для
пересылки бита 1 - сигнал SIGUSR2.
Первый процесс подтверждает получение каждого бита с помощью сигнала SIGALRM.
После завершения пересылки всего файла второй процесс посылает первому процессу
сигнал SIGIO.
Главный процесс должен дождаться завершения работы обоих процессов и завершиться
сам.
Использовать другие средства межпроцессного взаимодействия запрещено!
*/

#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

volatile sig_atomic_t bit;
volatile sig_atomic_t done;

void handleSigusr1(int s) {
  bit = 0; //
}

void handleSigusr2(int s) {
  bit = 1; //
}

void handleSigio(int s) {
  done = 1; //
}

void handleSigalrm(int s) {
  // Do nothing, interrupt pause()
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  int fd = open(argv[1], O_RDONLY);
  if (fd == -1) {
    perror("open");
    exit(EXIT_FAILURE);
  }

  signal(SIGALRM, handleSigalrm);
  pid_t pid1, pid2;

  if ((pid1 = fork()) == 0) {
    signal(SIGUSR1, handleSigusr1);
    signal(SIGUSR2, handleSigusr2);
    signal(SIGIO, handleSigio);

    char c = 0;
    int count = 0;

    while (!done) {
      sleep(1);
      c = (c << 1) | bit;
      count++;
      if (count == 8) {
        printf("%c", c);
        fflush(stdout);
        c = 0;
        count = 0;
      }
      kill(0, SIGALRM);
    }

    exit(EXIT_SUCCESS);
  }

  if ((pid2 = fork()) == 0) {
    char c;
    while (read(fd, &c, 1) > 0) {
      for (int i = 7; i >= 0; --i) {
        int bit = (c >> i) & 1; // Get i-th bit of c
        kill(pid1, bit ? SIGUSR2 : SIGUSR1);
        pause();
      }
    }

    kill(pid1, SIGIO);
    exit(EXIT_SUCCESS);
  }

  wait(NULL);
  wait(NULL);
  close(fd);

  return 0;
}