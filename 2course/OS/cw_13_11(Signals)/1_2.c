/*
2 Блокируется ли на время работы обработчика
а) тот же сигнал, что в данный момент обрабатывается
б) другие сигналы?
*/

#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void signal_handler(int signal) {
  printf("Handling signal %d\n", signal);
  sleep(5);
  printf("Signal %d handled\n", signal);
}

int main() {
    // struct sigaction sa;
    // sa.sa_handler = signal_handler;
    // sigemptyset(&sa.sa_mask);
    // sigaddset(&sa.sa_mask, SIGUSR1); // Блокировка SIGUSR1 во время обработки
    // sigaction(SIGINT, &sa, NULL);
  signal(SIGINT, signal_handler);

  printf("Waiting for SIGINT (Ctrl+C)...\n");
  while (1) {
    pause();
  }

  return 0;
}
