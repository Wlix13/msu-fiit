/* Написать программу, которая запускается с аргументами в командной строке и
для каждого из них печатает в стандартный вывод на отдельной строчке следующие
данные:

сам аргумент (строку), его длину, его последний символ, количество пробелов в
этом аргументе.

Для подсчета количества пробелов в строке написать отдельную функцию. */

#include <stdio.h>
#include <string.h>

int count_spaces(char *str) {
  int count = 0;
  for (int i = 0; i < strlen(str); i++) {
    if (str[i] == ' ')
      count++;
  }
  return count;
}

int main(int argc, char *argv[]) {
  for (int i = 1; i < argc; i++) {
    printf("Argument: `%s`; length: `%li`; last symbol: `%c`; spaces: `%d`\n",
           argv[i], strlen(argv[i]), argv[i][strlen(argv[i]) - 1],
           count_spaces(argv[i]));
  }
  return 0;
}
