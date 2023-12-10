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
1) с помощью семафоров
*/

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void process3(const char *filename, int N, key_t SEMAPHORE_KEY) {
  int semId = semget(SEMAPHORE_KEY, 3, IPC_CREAT | 0666);
  if (semId == -1) {
    perror("semaphore");
    exit(EXIT_FAILURE);
  }

  struct sembuf semaphore_operation;
  semaphore_operation.sem_flg = 0;
  semaphore_operation.sem_num = 0;
  semaphore_operation.sem_op = 1;
  semop(semId, &semaphore_operation, 1);

  semaphore_operation.sem_num = 2;
  semaphore_operation.sem_op = -1;
  semop(semId, &semaphore_operation, 1);

  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    perror("file open");
    exit(EXIT_FAILURE);
  }

  printf("Printing:\n");
  char c;
  while (fscanf(file, "%c", &c) != -1)
    printf("%c", c);

  fclose(file);

  if (semctl(semId, 0, IPC_RMID, NULL) == -1) {
    perror("semctl");
    exit(EXIT_FAILURE);
  }
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

  key_t SEMAPHORE_KEY = ftok(ipc_key_file, ipc_key_symbol);

  process3(shared_file, N, SEMAPHORE_KEY);

  return 0;
}