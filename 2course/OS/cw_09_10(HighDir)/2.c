/*
2. Написать программу, которая по бинарному файлу
(получен как результат работы п.1) создает его текстовую версию - числа в
текстовом виде через пробел. В командной строке передаются два имени файлов -
бинарного и текстового. Если второй файл уже существует, запросить подтверждение
на его изменение.
*/
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

void convert(char *filenameBin, char *filenameTxt) {
  int fdBin, fdTxt;
  int num;

  fdBin = open(filenameBin, O_RDONLY);

  //   Check if text file already exists
  fdTxt = open(filenameTxt, O_CREAT | O_WRONLY, 0666);
  if (fdTxt != -1) {
    char ans;
    printf("File %s already exists. Overwrite? (y/n) ", filenameTxt);
    scanf("%c", &ans);
    if (ans != 'y') {
      exit(0);
    }
  }

  if (fdBin == -1) {
    fprintf(stderr, "Error opening file %s\n", filenameBin);
    exit(1);
  }

  if (fdTxt == -1) {
    fprintf(stderr, "Error opening file %s\n", filenameTxt);
    exit(1);
  }

  while (read(fdBin, &num, sizeof(int))) {
    char buf[16];
    sprintf(buf, "%d ", num);
    write(fdTxt, buf, strlen(buf));
  }

  close(fdBin);
  close(fdTxt);
}

int main(int argc, char *argv[]) {
  if (argc != 3) {
    fprintf(stderr, "Usage: %s <filenameBinary> <filenameText>\n", argv[0]);
    exit(1);
  }

  // Convert binary file to text
  convert(argv[1], argv[2]);

  return 0;
}