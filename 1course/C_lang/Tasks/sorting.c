/* Реализовать любые ДВА разных алгоритма сортировки массива в виде функций и
проанализировать их работу.

void sort1(int *a, int n);
void sort2(int *a, int n);

Для анализа работы необходимо вычислить количество
основных операций (перестановок элементов и сравнений элементов) и вывести эти
значения в стандартный вывод для пяти видов массивов

Тип массива вводится с клавиатуры (1-5):
1) полностью упорядоченный
2) элементы в обратном порядке
3) все элементы массива равны
4,5) Произвольный массив, отличающийся от 1-3

Результатом выполнения задания должна быть программа с двумя функциями
сортировки и их вызовами из main  для указанных массивов. */

#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10


// Function for printing arrays and comment 
void print_array_comment(int *a, int n, char *c) {
  int i;
  printf("%s", c);
  for (i = 0; i < n; i++) {
    printf("%d ", a[i]);
  }
  printf("\n");
}

// Function for generating arrays
void array_gen(int *a, int n, int type) {
  int i;
  srand(time(NULL));

  switch (type) {
  // Pseudo-random array with ascending order
  case 1:
    a[0] = rand() % 100;
    for (i = 1; i < n; i++) {
      a[i] = a[i - 1] + rand() % 100;
    }
    break;

  // Pseudo-random array with descending order
  case 2:
    a[0] = rand() % 100;
    for (i = 1; i < n; i++) {
      int t = rand() % 100;
      // printf("%d", t);
      a[i] = a[i - 1] - t;
    }
    break;

  // All elements are equal
  case 3:
    for (i = 0; i < n; i++) {
      a[i] = 0;
    }
    break;

  // Random arrays
  case 4:
  case 5:
    for (i = 0; i < n; i++) {
      a[i] = rand() % 100;
    }
    break;

  // Undefined behaviour
  default:
    printf("Undefine type of array\n");
    exit(1);
  }
}

// Sort given array using bubble sort
void bubble_sort(int *a, int n) {
  int i, j, t;
  int perm = 0, compr = 0;

  for (i = 0; i < n - 1; i++) {
    for (j = 0; j < n - i - 1; j++) {
      compr++;
      if (a[j] > a[j + 1]) {
        t = a[j];
        a[j] = a[j + 1];
        a[j + 1] = t;
        perm++;
      }
    }
  }
  printf("Bubble sort: %d comparisions, %d permutations\n", compr, perm);
}

// Sort given array using insertion sort
void insertion_sort(int *a, int n) {
  int i, j, t;
  int perm = 0, compr = 0;

  for (i = 1; i < n; i++) {
    t = a[i];
    for (j = i - 1; j >= 0 && a[j] > t; j--) {
      compr++;
      a[j + 1] = a[j];
      perm++;
    }
    compr++;
    a[j + 1] = t;
  }
  printf("Insertion sort: %d comparisions; %d permutations\n", compr, perm);
}

int main() {
  int a[N], b[N];
  int type;

  // Input type of array
  printf("Enter type of array (1-5): ");
  scanf("%d", &type);

  // Generate array
  array_gen(a, N, type);
  print_array_comment(a, N, "Generated array: ");

  // Copy array a to array b to compare algorithms
  memcpy(b, a, N * sizeof(int));

  // Sort arrays
  bubble_sort(a, N);
  insertion_sort(b, N);

  // Print sorted arrays
  print_array_comment(a, N, "Bubble sorted: ");
  print_array_comment(b, N, "Insertion sorted: ");

  return 0;
}
