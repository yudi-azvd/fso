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
      printf("Exame de SO\n");
  }

  sleep(5); //  tem que esperar tempo o suficiente
}