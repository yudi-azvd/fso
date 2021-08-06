#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_CHILDREN 16
#define N_MAX 2000

int matrix_a[N_MAX][N_MAX];
int matrix_b[N_MAX][N_MAX];
int matrix_c[N_MAX][N_MAX];

int matrix_size;

enum step_t {
  CALCULATING = 0,
  PRINTING,
  FINISHED
};

typedef struct child {
  pid_t pid;
  int done_calc;
  int done_print;
  int step;
  int sig;
} child;


void init_children(child children[], int size) {
  int i = 0;
  for (; i < size; ++i) {
    children[i].step = CALCULATING;
    children[i].sig = i+1; // [1-16]
  }
}


void validate_nchildren(int nchildren) {
  if (nchildren < 1 || MAX_CHILDREN < nchildren) {
    printf("Número de processos inválido: %d\n", nchildren);
    printf("Intervalo válido para número de processos: [1, 16]\n");
    exit(1);
  }
}


void child_calc_your_part(int ma[N_MAX][N_MAX], int mb[N_MAX][N_MAX], int n, int start_row, int end_row) {
  int i, j, k;
  for (i = start_row; i <= end_row; ++i) {
    for (j = 0; j < n; ++j) {
      matrix_c[i][j] = 0; k = 0;
      while (k < n) {
        matrix_c[i][j] += matrix_a[i][k] * matrix_b[k][j];
        ++k;
      }
    }
  }
}


void print_matrix(int m[N_MAX][N_MAX], int n, int start_row, int end_row) {
  int i = 0, j = 0;
  for (i = start_row; i <= end_row; ++i) {
    for (j = 0; j < n-1; ++j) {
      printf("%d ", m[i][j]);
    }
    printf("%d\n", m[i][j]);
  }
}


void child_do_nothing(int sig) {return;}
#endif
