/* В основной программе написать функцию int ncolumns(Int**, int,int),
   вычисляющую количество нулевых столбцов в матрице размера N x M, в функции
   main создать тестовую матрицу, продемонстрировать работу функции.
*/

#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>

#define N 3 // rows
#define M 4 // coloms

int ncolumns(int **a, int n, int m) {
  int count = 0;
  for (int i = 0; i < m; i++) {
    int flag = 0;
    for (int j = 0; j < n; j++) {
      if (a[j][i] != 0) {
        flag = 1;
        break;
      }
    }
    if (flag == 0)
      count++;
  }
  return count;
}

int main() {
  int **a = create_matrix(N, M);
  in_mat(a, N, M);

  printf("Matrix:\n");
  print_mat(a, N, M);

  printf("Number of zero columns: %d", ncolumns(a, N, M));
  del_mat(a, N);
}