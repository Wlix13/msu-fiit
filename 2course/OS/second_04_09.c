/*
Считывать со стандартного ввода символы до признока конца файла. Из введённых
цифр сформировать целое число типа int, остальные символы пропускать. После
ввода очередной цифры выводить текущее число. Переполнения не допускать, а
начинать создание новго числа
*/

#include <stdio.h>
#include <limits.h>


int main() {
  char ch;
  int num = 0;

  while ((ch = getchar()) != EOF) {
    if (ch >= '0' && ch <= '9') {
      int digit = ch - '0';

      if (num > (INT_MAX - digit) / 10) {
        printf("Overflow detected, starting a new number.\n");
        num = 0;
      }
      num = num * 10 + digit;
    }

    printf("Current number: %d\n", num);
  }

  return 0;
}