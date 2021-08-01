#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

#define N_MAX 2000

#define PRINT_YOUR_HALF SIGINT
#define CHILD_1_SIGNAL SIGUSR1
#define CHILD_2_SIGNAL SIGUSR2

static void child_do_nothing(int sig) {return;};
void parent_handle_child_1_sig(int);
void parent_handle_child_2_sig(int);
void child_calc_your_half(int ma[N_MAX][N_MAX], int mb[N_MAX][N_MAX], int n, int start_row, int end_row);
void child_1_print_your_half(int sig);
void child_2_print_your_half(int sig);
void print_matrix(int m[N_MAX][N_MAX], int n, int start_row, int end_row);
void read_matrices();

int matrix_a[N_MAX][N_MAX];
int matrix_b[N_MAX][N_MAX];
int matrix_c[N_MAX][N_MAX];

int status;
int n = 0, children_done_calc = 0, children_done_print = 0;
int child_1_done_calc = 0, child_2_done_calc = 0;
int child_1_done_print = 0, child_2_done_print = 0;
int child_1_sig = 0, child_2_sig = 0;
pid_t child_pid_1, child_pid_2;


/**
 * Solução do professor:
 * https://www.youtube.com/watch?v=YzaDM4QHjN8
 * 
 * Notar o que ele fala em t=14m12s sobre usar a mesma variável que é 
 * influenciada por processos diferentes.
 * 
 * Ideia para o futuro: rodar o profiler nesse programa e ver onde ele mais 
 * gasta tempo.
 */
int main() {
  int i;
  const int nproc = 2;
  pid_t pids[nproc];
  signal(CHILD_1_SIGNAL, parent_handle_child_1_sig);
  signal(CHILD_2_SIGNAL, parent_handle_child_2_sig);
  int child_sigs[] = {CHILD_1_SIGNAL, CHILD_2_SIGNAL};

  scanf("%d\n", &n);
  read_matrices();

  int interval_len = n / nproc;
  int remainder = n % nproc; // A última iteração do for tem que cuidar das
                             // últimas remainder linhas.
  for (i = 0; i < nproc; ++i) {
    pids[i] = fork();

    if (pids[i] == 0) {
      // poderia colocar esse bloco numa função, tirando o exit(0) e pause() e kill()?;
      int start_row = i*interval_len, end_row = i*interval_len+interval_len-1;
      signal(CHILD_1_SIGNAL, child_do_nothing);
      child_calc_your_half(matrix_a, matrix_b, n, start_row, end_row);
      kill(getppid(), child_sigs[i]);
      pause();
      print_matrix(matrix_c, n, start_row, end_row);
      kill(getppid(), child_sigs[i]);
      exit(0);
    }
  }

  // printf("(%d) waiting for children to calc\n", getpid());
  while (child_1_sig == 0 || child_2_sig == 0) {
    pause();
  }

  kill(child_pid_1, CHILD_1_SIGNAL);
  pause();
  kill(child_pid_2, CHILD_2_SIGNAL);

  wait(NULL);
  wait(NULL);
  return 0;
}


void parent_handle_child_1_sig(int sig) {
  child_1_sig++;
  // printf("child 1 sent signal: %d\n", child_1_sig);
}


void parent_handle_child_2_sig(int sig) {
  child_2_sig++;
  // printf("child 2 sent signal: %d\n", child_2_sig);
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
        matrix_c[i][j] += matrix_a[i][k] * matrix_b[k][j];
        ++k;
      }
    }
  }
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
