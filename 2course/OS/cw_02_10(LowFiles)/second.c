/*
2) Создать массив для хранения информации о строках файла, он нужен для решения
следующих задач:

а) В интерактивном режиме по номеру строки в файле на экран выдавать её
содержимое. Нужно обеспечить "быстрый доступ" к строкам файла, без прохода по
файлу. Считывать файл и строки в память целиком нельзя.
Использовать функции:
int fseek (FILE *stream, long offset, int origin);
long ftell (FILE *stream);
*/

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int main(int argc, char *argv[]) {
  FILE *fp;
  long count = 0;
  long line_num, i;
  long *offsets;
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
  count++;

  offsets = (long *)malloc(count * sizeof(long));

  if (offsets == NULL) {
    fprintf(stderr, "Can't allocate memory\n");
    exit(1);
  }

  fseek(fp, 0, SEEK_SET);
  offsets[0] = 0;

  for (i = 1; i < count; i++) {
    while ((c = fgetc(fp)) != '\n' && c != EOF) {
      if (c == EOF) {
        break;
      }
    }
    offsets[i] = ftell(fp);
  }

  while (1) {
    printf("Enter line number (0 to exit): ");
    scanf("%ld", &line_num);
    if (line_num == 0) {
      break;
    }
    if (line_num < 1 || line_num > count) {
      printf("Invalid line number.\n");
    } else {
      fseek(fp, offsets[line_num - 1], SEEK_SET);
      while ((c = fgetc(fp)) != '\n') {
        printf("%c", c);
      }
      printf("\n");
    }
  }

  free(offsets);
  fclose(fp);

  return 0;
}