#include <stdio.h>

#include "main.h"

// Muito parecido com o Multiplicação de Matriz do MOJ
// só que N processos
// https://www.brunoribas.com.br/so/2019-1/pratica/multiplicacao-matriz.html#exemplo-de-entrada
// https://moj.naquadah.com.br/contests/bcr-FSO-2021_1-processos-e-sinais/multiplica-matriz-fork.html
int nchildren;
child children[MAX_CHILDREN];


void read_matrices() {
  int i = 0, j = 0;
  for (i = 0; i < matrix_size; ++i)
    for (j = 0; j < matrix_size; ++j)
      scanf("%d", &matrix_a[i][j]);

  for (i = 0; i < matrix_size; ++i)
    for (j = 0; j < matrix_size; ++j)
      scanf("%d", &matrix_b[i][j]);
}


int children_are_done_calculating() {
  int i = 0;
  for (; i < nchildren; i++)
    if (children[i].step <= CALCULATING)
      return 0;
  return 1;
}

void parent_handle_signal(int sig) {
  // fprintf(stderr, "parent received signal %d\n", sig);
  int child_index = sig-1;
  children[child_index].step++;

  if (children[child_index].step == PRINTING) {
    children[child_index].step++;
  }

  // printf("children_are_done_calculating: %d\n", children_are_done_calculating());
  // int i = 0;
  // for (; i < nchildren; i++)
  //   printf("child[%d].step = %d\n", i, children[i].step);
}


// mapeamento "1 pra 1" de sinais pra procesoss filhos
void install_signals(int nchildren) {
  int i = 1;
  for (; i <= nchildren; ++i) {
    signal(i, parent_handle_signal);
  }
}


// ./a.out <número de processos> < matriz-01.in
// número de processos: 1 - 16
// exemplo:
// ./a.out 4 < matriz-01.in
int main(int argc, char** argv) {
  printf("(%d) parent created\n", getpid());

  int i;
  nchildren = atoi(argv[1]);

  validate_nchildren(nchildren);
  install_signals(nchildren);
  init_children(children, nchildren);

  scanf("%d\n", &matrix_size);
  read_matrices();

  int start_row, end_row;
  int row_interval_size = matrix_size / nchildren;
  int remainder = matrix_size % nchildren;
  int limit = remainder == 0 ? nchildren : nchildren-1;
  for (i = 0; i < limit; ++i) {
    children[i].pid = fork();

    if (children[i].pid == 0) {
      start_row = i*row_interval_size;
      end_row = start_row+row_interval_size-1;
      signal(SIGINT, child_do_nothing);
      printf("  (%d) child, my rows: [%d, %d]\n", getpid(), start_row, end_row);
      child_calc_your_part(matrix_a, matrix_b, matrix_size, start_row, end_row);
      kill(getppid(), children[i].sig);
      pause();
      print_matrix(matrix_c, matrix_size, start_row, end_row);
      kill(getppid(), children[i].sig);
      exit(0);
    }
  }
  
  // o último processo fica com a sua parte mais o resto da divisão.
  if (remainder > 0) {
    children[i].pid = fork();

    if (children[i].pid == 0) {
      start_row = i*row_interval_size;
      end_row = matrix_size-1;
      signal(SIGINT, child_do_nothing);
      usleep(i*1000);
      printf("  -- remainder\n");
      printf("  (%d) child, my rows: [%d, %d]\n", getpid(), start_row, end_row);
      child_calc_your_part(matrix_a, matrix_b, matrix_size, start_row, end_row);
      kill(getppid(), children[i].sig);
      pause();
      print_matrix(matrix_c, matrix_size, start_row, end_row);
      kill(getppid(), children[i].sig);
      exit(0);
    }
  }

  // melhor esperar nchildren vezes?
  while (!children_are_done_calculating())
    pause();
  
  printf("(%d) children done calculating\n", getpid());

  // uma rotina que:
  // se o filho anterior terminou, manda o proximo imprimir
  i = 0;
  while (i < nchildren) {
    kill(children[i++].pid, SIGINT);
    pause();
  }

  i = nchildren;
  int status;
  while (i--) {
    wait(&status);
  }

  return 0;
}
