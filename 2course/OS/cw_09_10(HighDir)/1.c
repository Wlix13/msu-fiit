/*
1. В командной строке передаются имя файла и число N.
Создать бинарный файл, содержащий 32-битные целые знаковые числа разных знаков.
Количество чисел N. Числа задать случайным образом, знак очередного числа
задавать тоже случайно.
Использовать функции (определены в <stdlib.h>) :
int rand (void) - генерирует последовательность (псевдо)случайных чисел из
диапазона [0..RAND_MAX]
void srand (unsigned int) - устанавливает исходное число для последовательности,
генерируемой функцией rand()
*/

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

void genBin(char *filename, int N) {
  int fdBin;

  fdBin = open(filename, O_CREAT | O_RDWR, 0666);

  if (fdBin == -1) {
    fprintf(stderr, "Error opening file %s\n", filename);
    exit(1);
  }

  srand(time(NULL));
  for (int i = 0; i < N; i++) {
    int num = arc4random() % 100;
    if (arc4random() % 2) {
      num *= -1;
    }
    write(fdBin, &num, sizeof(int));
  }

  close(fdBin);
}

int main(int argc, char *argv[]) {
  int N;

  if (argc != 3) {
    fprintf(stderr, "Usage: %s <filenameBinary> <N>\n", argv[0]);
    exit(1);
  }

  N = strtol(argv[2], NULL, 10);

  // Generate binary file
  genBin(argv[1], N);

  return 0;
}