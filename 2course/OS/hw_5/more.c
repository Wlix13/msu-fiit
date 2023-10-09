/*
Обязательно контролировать наличие параметров в командной строке и успешность
открытия файлов. Учесть, что исходные файлы могут быть пустыми.

Написать программу, работающую подобно команде more, которая осуществляет вывод
файла на экран порциями по нажатию клавиши <пробел> (можете выбрать любую).

Нажатие <q> - прервать работу (дальше не выводить файл).

more [-s] [-num] [+linenum] файл

Опции:

-s – предписывает заменять последовательность пустых строк одной пустой строкой.
-num - целое число задает количество выводимых за один раз строк.
(Длина одной порции по умолчанию, если эта опция не задана 10 строк)
+linenum - начать вывод со строки с номером linenum (целое число >=1)

Порядок опций определен, любая из них (в том числе и все) при запуске программы
может отсутствовать.

Примеры вызова:
> ./more -s -6 +10 file
> ./more -16 file
> ./more file
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  FILE *file;
  char line[1024];
  char *filename = NULL;

  // Default values
  int lines_to_display = 10;
  int start_line = 0;
  int suppress_empty = 0;
  int previous_empty = 0;

  // Parse arguments(support diferent order)
  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-s") == 0) {
      suppress_empty = 1;
    } else if (argv[i][0] == '-') {
      lines_to_display = atoi(argv[i] + 1);
    } else if (argv[i][0] == '+') {
      start_line = atoi(argv[i] + 1) - 1;
    } else {
      filename = argv[i];
    }
  }

  if (!filename) {
    fprintf(stderr, "No file provided.\n");
    exit(1);
  }

  if ((file = fopen(filename, "r")) == NULL) {
    fprintf(stderr, "Error opening file %s\n", filename);
    exit(1);
  }

  // Skip lines (argument +N)
  for (int i = 0; i < start_line; i++) {
    if (!fgets(line, sizeof(line), file)) {
      break;
    }
  }

  int lines_shown = 0;
  while (fgets(line, sizeof(line), file)) {
    // Check if line is empty
    // if we need to suppress empty lines (argument -s)
    if (suppress_empty && (line[0] == '\n' || line[0] == '\r')) {
      if (previous_empty) {
        continue;
      }
      previous_empty = 1;
    } else {
      previous_empty = 0;
    }

    printf("%s", line);
    lines_shown++;

    // Check if we need to pause (argument -num)
    if (lines_shown >= lines_to_display) {
      // Can be commented out to make output more clear
      printf("\nPress space to continue, q to quit.");

      char ch = getchar();
      if (ch == 'q' || ch == 'Q') {
        break;
      }

      //   Another block of lines is shown
      lines_shown = 0;
    }
  }

  fclose(file);
  return 0;
}
