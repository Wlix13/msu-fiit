/*
Работают 3 НЕ родственных процесса.
Каждый в командной строке получает имя файла (должен существовать) и символ для
формирования ключа IРС, а также имя файла, который является разделяемым
ресурсом, и число N — задает продолжительность работы.
В цикле от 1 до N каждый выполняет свою работу. 1 и 2 процессы пишут в файл
строго по очереди по одной строке:
1-ый - свой pid и номер итерации,
2-ой - свой pid и какое-нибудь сообщение. Строка должна заканчиваться \n.
После того, как 1 и 2 закончили писать, 3-ий читает написанные строки из файла и
выводит на экран. Синхронизировать работу процессов
2) с помощью очереди сообщений.
*/

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

typedef struct {
  long mtype;    // Message type
  char mtext[1]; // Message text
} message_t;

void process2(const char *filename, int N, int msgId) {
  FILE *file = fopen(filename, "a");
  if (file == NULL) {
    perror("file open");
    exit(EXIT_FAILURE);
  }

  message_t msg;

  for (int i = 1; i <= N; i++) {
    // Wait for message to start writing
    if (msgrcv(msgId, &msg, sizeof(msg.mtext), 2, 0) == -1) {
      perror("msgrcv");
      exit(EXIT_FAILURE);
    }

    fprintf(file, "Process 2: PID - %d - Hello World!\n", getpid());
    fflush(file);

    // Send message to process 1
    msg.mtype = 1;
    if (msgsnd(msgId, &msg, sizeof(msg.mtext), 0) == -1) {
      perror("msgsnd");
      exit(EXIT_FAILURE);
    }
  }

  fclose(file);
}

int main(int argc, char **argv) {
  if (argc < 5) {
    fprintf(
        stderr,
        "Usage: %s <file_for_ipc_key> <symbol_for_ipc_key> <shared_file> <N>\n",
        argv[0]);
    exit(EXIT_FAILURE);
  }

  char *ipc_key_file = argv[1];
  int ipc_key_symbol = atoi(argv[2]);
  char *shared_file = argv[3];
  int N = atoi(argv[4]);

  key_t key = ftok(ipc_key_file, ipc_key_symbol);
  int msgId = msgget(key, IPC_CREAT | 0666);
  if (msgId == -1) {
    perror("msgget");
    exit(EXIT_FAILURE);
  }

  process2(shared_file, N, msgId);

  // Cleanup message queue
  if (msgctl(msgId, IPC_RMID, NULL) == -1) {
    perror("msgctl");
    exit(EXIT_FAILURE);
  }

  return 0;
}
