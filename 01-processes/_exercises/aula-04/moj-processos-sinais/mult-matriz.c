#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

#define N_MAX 10

int matrix_a[N_MAX][N_MAX] = {
  {1, 2},
  {3, 4}
};
int matrix_b[N_MAX][N_MAX] = {
  {9, 8},
  {7, 6}
};

int matrix_c[N_MAX][N_MAX];


void print_matrix(int m[N_MAX][N_MAX], int n, int start_row, int end_row) {
  int i = 0, j = 0;
  for (i = start_row; i <= end_row; ++i) {
    for (j = 0; j < n-1; ++j) {
      printf("%d ", m[i][j]);
    }
    printf("%d\n", m[i][j]);
  }
}

// lembrando como que faz multiplicação de matrizes
// nem precisei pesquisar B-)
int main() {
  int n=2, i, j, k;

  for (i = 0; i < n; ++i) {
    for (j = 0; j < n; ++j) {
      matrix_c[i][j] = 0; k = 0;
      while (k < n) {
        matrix_c[i][j] += matrix_a[i][k] * matrix_b[k][j];
        ++k;
      }
    }
  }

  print_matrix(matrix_a, n, 0, n-1);
  print_matrix(matrix_b, n, 0, n-1);
  print_matrix(matrix_c, n, 0, n-1);
  return 0;
}
