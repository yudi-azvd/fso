#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

// exercpicio 9
// https://www.brunoribas.com.br/so/2021-1/#orgb5ea29f
int main() {
  int i, j, nchildren = 6;
  pid_t p;

  int start_number, end_number;
  int interval_size = 1200 / nchildren;
  int limit;
  for (i = 0; i < nchildren; i++) {
    p = fork();

    if (p == 0) {
      start_number = i * interval_size;
      end_number = start_number + interval_size;
      for (j = start_number+1; j < end_number; j++) {
        printf("%d ", j);
      }
      printf("%d\n\n", j);
      exit(0);
    }
    // else 
    //   wait(NULL); // sequencial
  }

  sleep(2); // pra dar tempo de todos os filhos imprimirem
  i = nchildren;
  while (i--) {
    wait(NULL);
  }
  return 0;
}
