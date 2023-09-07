/*
В командной строке передаются числа и строки в призвольном порядке
Строка считается числом, если она полностью представляет число.

1) Объединить строки в одну строку, а счила сложить. Для представления
использовать strtod За один раз выделить участок памяти не более необходимого
максимального объёма.

2) Написать функцию, которая сортирует строку по возрастанию ASCII кода символа.

3) Написать функцию double_rev(double x), которая по полученному числу строит
число, запись которого явлется реверсом исходного числа 0 -> 0 12.34 -> 43.21
-123.456 -> -654.321

*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void sort(char *str) {
  int len = strlen(str);
  for (int i = 0; i < len; i++) {
    for (int j = 0; j < len - i - 1; j++) {
      if (str[j] > str[j + 1]) {
        char tmp = str[j];
        str[j] = str[j + 1];
        str[j + 1] = tmp;
      }
    }
  }
}

double double_rev(double x) {
  int sign = (x < 0) ? -1 : 1;
  char str[50];
  sprintf(str, "%f", x);

  int len = strlen(str);
  char rev_str[len + 1];

  for (int i = 0; i < len; i++) {
    rev_str[i] = str[len - i - 1];
  }
  rev_str[len] = '\0';

  return sign * atof(rev_str);
}

int main(int argc, char *argv[]) {
  long MAX_LEN = 0;

  for (int i = 1; i < argc; i++) {
    char *endptr;
    double num = strtod(argv[i], &endptr);
    if (*endptr != '\0') {
      MAX_LEN += strlen(argv[i]);
    }
  }

  double sum = 0;
  char *str = malloc(MAX_LEN * sizeof(char));
  str[0] = '\0';

  for (int i = 1; i < argc; i++) {
    char *endptr;
    double num = strtod(argv[i], &endptr);
    if (*endptr == '\0') {
      sum += num;
    } else {
      strcat(str, argv[i]);
    }
  }

  printf("Sum: %lf\n", sum);
  printf("String: %s\n", str);

  sort(str);
  printf("Sorted string: %s\n", str);

  printf("Reversed double: %lg\n", double_rev(sum));

  free(str);
}
