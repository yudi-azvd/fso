#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

// DICA: a chave está em entender que FORK retorna DUAS vezes:
// uma no pai e outra no fiho

// ./a.out & ps -x --forest
int main() {
  int i;
  pid_t pid1, pid2;
  pid2 = 0;

  for (i = 0; i < 2; i++) {
    pid1 = fork();
    
    if (pid1 == 0)
      pid2 = fork();
    
    if (pid2 == 0)
      printf("(%d) Exame de SO\n", getpid());
  }

  pause();
}

/*
10490 \_ ./a.out
10491     \_ ./a.out
10492     |   \_ ./a.out
10497     |   |   \_ ./a.out
10498     |   |       \_ ./a.out
10493     |   \_ ./a.out
10496     |       \_ ./a.out
10494     \_ ./a.out
10495         \_ ./a.out

(10490) Exame de SO
(10490) Exame de SO
(10492) Exame de SO
(10495) Exame de SO
(10492) Exame de SO
(10498) Exame de SO
(10496) Exame de SO
*/
