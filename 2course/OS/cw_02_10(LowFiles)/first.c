/*
Программа. В командной строке передаётся имя файла. Файл содержит текстовые
строки, файл может быть и пустым.

1) Пройти по файлу, чтобы определить количество строк в файле. Вывести его на
экран. Если в конце последней строки файла нет символа "\n', приписать его.
Создать файл без \n в конце можно командой cat >file , закончив последнюю строку
вводом EOF.
*/

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int main(int argc, char *argv[]) {
  FILE *fp;
  int count = 0;
  char c;

  if (argc != 2) {
    fprintf(stderr, "Usage: %s <имя файла>\n", argv[0]);
    exit(1);
  }
  if ((fp = fopen(argv[1], "r+")) == NULL) {
    fprintf(stderr, "Can't open %s\n", argv[1]);
    exit(1);
  }

  while ((c = fgetc(fp)) != EOF) {
    if (c == '\n') {
      count++;
    }
  }

  if (c != '\n') {
    count++;
    fprintf(fp, "\n");
  }

  printf("Количество строк в файле: %d\n", count);

  fclose(fp);
  return 0;
}