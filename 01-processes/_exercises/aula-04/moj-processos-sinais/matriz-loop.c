#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

#define N_MAX 2000

#define DONE_CALC SIGALRM
#define PRINT_YOUR_HALF SIGUSR1
#define DONE_PRINT SIGINT

void parent_handle_done_calc(int);
void parent_handle_done_print(int);
void read_matrices();
void child_calc_your_half(int ma[N_MAX][N_MAX], int mb[N_MAX][N_MAX], int n, int start_row, int end_row);
void print_matrix(int m[N_MAX][N_MAX], int n, int start_row, int end_row);
void child_1_print_your_half(int sig);
void child_2_print_your_half(int sig);

int matrix_a[N_MAX][N_MAX];
int matrix_b[N_MAX][N_MAX];
int matrix_c[N_MAX][N_MAX];

const int nproc = 2;
int n = 0, children_done_calc = 0, children_done_print = 0;
int status;
pid_t child_pid_1, child_pid_2;


/**
 * Solução do professor:
 * https://www.youtube.com/watch?v=LXcm3EFv86I&t=2732s
 * 
 * Notar o que ele fala em t=4019 sobre usar a mesma variável pra uma coisa lá.
 * 
 * Ideia para o futuro: rodar o profiler nesse programa e ver onde ele mais 
 * gasta tempo.
*/
int main() {
  signal(DONE_CALC, parent_handle_done_calc);
  signal(DONE_PRINT, parent_handle_done_print);

  scanf("%d", &n);
  read_matrices();

  child_pid_1 = fork();
  if (child_pid_1 > 0) {

    // calculate lower half
    child_pid_2 = fork();
    if (child_pid_2 == 0) {
      signal(PRINT_YOUR_HALF, child_2_print_your_half);
      child_calc_your_half(matrix_a, matrix_b, n, n/2, n-1);
      kill(getppid(), DONE_CALC);
    }
  }

  // calculate upper half
  if (child_pid_1 == 0) {
    signal(PRINT_YOUR_HALF, child_1_print_your_half);
    child_calc_your_half(matrix_a, matrix_b, n, 0, n/2-1);
    kill(getppid(), DONE_CALC);
  }

  // printf("(%d) ON PAUSE!\n", getpid());
  while (children_done_print < 2) {
    pause();
  }

  return 0;
}


void parent_handle_done_calc(int sig) {
  ++children_done_calc;

  if (children_done_calc == 2) {
    kill(child_pid_1, PRINT_YOUR_HALF);
    // não basta esperar um tempo fixo (usleep(1)), o pai deve esperar
    // o filho1 terminar de imprimir - pause()
    pause();
    kill(child_pid_2, PRINT_YOUR_HALF);
  }
}


void parent_handle_done_print(int sig) {
  ++children_done_print;
  // printf("(%d) children_done_print=%d\n", getpid(), children_done_print);

  if (children_done_print == 1) {
    waitpid(child_pid_1, &status, 0);
  }

  if (children_done_print == 2) {
    waitpid(child_pid_2, &status, 0);
    exit(0);
  }
}


void child_calc_your_half(int ma[N_MAX][N_MAX], int mb[N_MAX][N_MAX], int n, int start_row, int end_row) {
  int i, j, k;
  for (i = start_row; i <= end_row; ++i) {
    for (j = 0; j < n; ++j) {
      matrix_c[i][j] = 0; k = 0;
      while (k < n) {
        printf("(%d) mult\n", getpid());
        matrix_c[i][j] += matrix_a[i][k] * matrix_b[k][j];
        ++k;
      }
    }
  }
}


void child_1_print_your_half(int sig) {
  print_matrix(matrix_c, n, 0, n/2-1);
  kill(getppid(), DONE_PRINT);
  exit(0);
}


void child_2_print_your_half(int sig) {
  print_matrix(matrix_c, n, n/2, n-1);
  kill(getppid(), DONE_PRINT);
  exit(0);
}


void read_matrices() {
  int i = 0, j = 0;
  for (i = 0; i < n; ++i)
    for (j = 0; j < n; ++j)
      scanf("%d", &matrix_a[i][j]);

  for (i = 0; i < n; ++i)
    for (j = 0; j < n; ++j)
      scanf("%d", &matrix_b[i][j]);
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
