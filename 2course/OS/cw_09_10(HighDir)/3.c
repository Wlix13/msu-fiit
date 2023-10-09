/*
3. В командной строке передаётся имя файла (получен как результат работы п.1).
Переставить в файле числа так, чтобы в начале файла располагались отрицательные
числа, а в конце — неотрицательные. Порядок чисел среди чисел одного знака
произвольный. Файл в память целиком не считывать, можно одновременно считывать
не более 10 чисел файла. Временный файл создавать нельзя. Учесть, что файл может
быть пустым, может содержать только числа одного знака.
*/
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

void swap(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

void rearrangeFile(char *filename) {
  int fdBin;

  fdBin = open(filename, O_RDWR);

  if (fdBin == -1) {
    fprintf(stderr, "Error opening file %s\n", filename);
    exit(1);
  }

  struct stat st;
  fstat(fdBin, &st);

  off_t start = 0;
  off_t end = st.st_size - sizeof(int);

  int numStart, numEnd;

  while (start < end) {
    numStart = numEnd = 0;

    //  Read the values of numStart and numEnd from the binary file.
    lseek(fdBin, start, SEEK_SET);
    read(fdBin, &numStart, sizeof(int));
    lseek(fdBin, end, SEEK_SET);
    read(fdBin, &numEnd, sizeof(int));

    //   Swap the values of numStart and numEnd in the binary file.
    if (numStart >= 0 && numEnd < 0) {
      swap(&numStart, &numEnd); // Now numStart < 0 and numEnd >= 0
      lseek(fdBin, start, SEEK_SET);
      write(fdBin, &numStart, sizeof(int));
      lseek(fdBin, end, SEEK_SET);
      write(fdBin, &numEnd, sizeof(int));
    }

    // Move the start and end pointers.
    if (numStart < 0)
      start += sizeof(int);
    if (numEnd >= 0)
      end -= sizeof(int);
  }

  close(fdBin);
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <filenameBinary>\n", argv[0]);
    exit(1);
  }

  // Rearrange file
  rearrangeFile(argv[1]);

  return 0;
}