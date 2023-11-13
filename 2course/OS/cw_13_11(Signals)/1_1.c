/*
1 Сбрасывается ли обработка сигнала на значение по умолчанию после вызова
обработчика, если нет его явной переустановки?
*/

#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void signal_handler(int sig) { printf("Signal %d handled\n", sig); }

int main() {
  signal(SIGINT, signal_handler);
  printf("Waiting for SIGINT (Ctrl+C)...\n");
  pause();

  printf("Waiting for SIGINT second time...\n");
  pause();

  return 0;
}
