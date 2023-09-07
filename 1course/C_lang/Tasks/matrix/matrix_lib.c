/*

Custom library to handle NxM matrix operations(without memory leaks)
1) Matrix creation
2) Matrix addition from keyboard
3) Matrix deletion

*/

#include <stdio.h>
#include <stdlib.h>

/*
Function gets two int numbers: N and M - rows and coloms
Create matrix(int **) with N rows and M coloms
Return:
    'int **' - pointer to pointer to int
*/
int **create_matrix(int N, int M) {
  int **A = (int **)malloc(N * sizeof(int *));
  for (int i = 0; i < N; i++) {
    A[i] = (int *)malloc(M * sizeof(int));
  }
  return A;
}

/*
Function gets: int **A - matrix and int N - rows in Matrix
Free all allocated memory for matrix
Return:
    'void'
*/
void del_mat(int **A, int N) {
  for (int i = 0; i < N; i++) {
    free(A[i]);
  }
  free(A);
}

/*
Function gets: int **A - matrix, int N - rows in Matrix, int M - coloms
Fill matrix with numbers from keyboard
Return:
  'void'
*/
void in_mat(int **A, int N, int M) {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      scanf("%d", &A[i][j]);
    }
  }
}

/*
Function gets: int **A - matrix, int N - rows in Matrix, int M - coloms
Print matrix to stdout
Return:
  'void'
*/
void print_mat(int **A, int N, int M) {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      printf("%d ", A[i][j]);
    }
    printf("\n");
  }
}