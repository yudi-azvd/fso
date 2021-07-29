#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/**
 * ./a.out & ps -x --forest | grep -B 2 -A 2 './a.out' > tmp; code tmp
 * 
 * Adicionar sed pra cortar umas partes desnecessárias
 * 
 * **************************
 * // getpid(), child_pid, (child_exit_status & 0xff00) >> 8); // ???????
 * // getpid(), child_pid, (child_exit_status & 0xff00)); // ??????? 
 */

void child_do() {
  printf("FILHO(%d) - meu pai é %d\n", getpid(), getppid());
  sleep(1);
  printf("FILHO(%d) - terminei\n", getpid());
  exit(3);
}

void parent_do() {
  printf("PAI(%d) - vou esperar meu filho terminar\n", getpid());
  int child_exit_status;
  pid_t child_pid = wait(&child_exit_status);

  // 8 bits menos significativos do STATUS o retorno
  printf("PAI(%d) - terminei logo depois do meu"
    " filho(%d) que terminou com status %d\n", 
    getpid(), child_pid, WEXITSTATUS(child_exit_status));
}


int main() {
  int seconds = 5;
  pid_t pid = fork();

  if (pid > 0) { // PROCESSO PAI
    parent_do();
  }
  else if (pid == 0) { // PROCESSO FILHO
    child_do();
  }

  sleep(5);

  return 0;
}