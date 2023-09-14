/*
1) Написать функцию, которая выводи на экран двоичное представление. Незначащие
нули тоже выводить. Отрицательные выводить в их внутреннем представлении.
(наприме, -1 выводится как последовательность единиц)


2) Написать функцию, аргументы которой указатель на массив из char, длина
массива, и число n. Вернуть значение n-го бита в заданном массиве. Рассмотреть 2
случая нумерации битов:

a) Биты в байте нумеруются с 0 и справа налево
b) Сплошная нумерация битов от 0 до len_max


3) Написать функцию, аргументы которой указатель на массив из char, длина
массива в байтах и целое число n.

а) Подсчитать в массиве количество областе из подряд идущих единиц, длина
которых больше или равна n
б) Определить максимальную область из подряд идущих
единиц Используется сплошная нумерация битов
*/

#include <stdio.h>
#include <stdlib.h>

void print_bin(char x) {
  int i;
  for (i = 7; i >= 0; i--) {
    printf("%d", (x >> i) & 1);
  }
  //   printf("\n");
}

// Function to get the nth bit of an array
int getBit(char *arr, int len, int n, int case_num) {
  int bytePos = 0;
  int bitPos = 0;

  if (case_num == 1) {
    bytePos = n / 8;
    bitPos = n % 8;
  } else if (case_num == 2) {
    bytePos = n / 8;
    bitPos = 7 - (n % 8);
  }

  if (bytePos >= len) {
    printf("Error: Bit position is out of array bounds.\n");
    return -1;
  }

  return (arr[bytePos] >> bitPos) & 1;
}

int ones_count(char *arr, int len, int n) {
  int i;
  int count = 0;
  int area_count = 0;
  int max_count = 0;

  for (i = 0; i < len * 8; i++) {
    if (getBit(arr, len, i, 2) == 1) {
      count++;
    } else {
      if (count >= n) {
        printf("Detected an area of ones: %d\n", count);
        area_count++;
      }
      if (count > max_count) {
        max_count = count;
      }
      count = 0;
    }
  }

  printf("Max count of ones: %d\n", max_count);
  return area_count;
}

int main() {

  char arr[] = {0x3A, 0x6D};
  int len = sizeof(arr);
  int n = 2;

  print_bin(arr[0]);
  print_bin(arr[1]);
  printf("\n");

  //   printf("The %dth bit is: %d\n", n, getBit(arr, len, n, 1));
  //   printf("The %dth bit is: %d\n", n, getBit(arr, len, n, 2));

  int areas = ones_count(arr, len, n);
  printf("Areas total: %d\n", areas);
  return 0;
}