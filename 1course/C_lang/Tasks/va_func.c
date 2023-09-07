/* Написать функцию с переменным числом параметров, которая получает в качестве
параметров количество чисел (unsigned) и сами числа (int), для которых требуется
вычислить среднее арифметическое (double).

Рекомендуется использовать библиотеку stdarg.h */

#include <stdarg.h>
#include <stdio.h>

double calculate_mean(unsigned count, ...) {
  va_list args;
  int sum = 0;

  va_start(args, count);
  for (unsigned i = 0; i < count; i++) {
    int num = va_arg(args, int);
    sum += num;
  }
  va_end(args);

  return (double)sum / count;
}

int main() {
  double mean = calculate_mean(4, 10, 25, 30, 40);
  printf("The arithmetic mean is: %lf\n", mean);

  mean = calculate_mean(3, -5, 0, 5);
  printf("The arithmetic mean is: %lf\n", mean);

  return 0;
}