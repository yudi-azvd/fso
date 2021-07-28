#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// ./a.out 5
int main() {
  int seconds = 5;
  pid_t pid = fork();

  if (pid > 0) { // PROCESSO PAI
    printf("PAI - sou o pai. meu filho é %d\n", pid);
    printf("PAI - não vou esperar meu filho terminar...\n");
    sleep(50); // o pai tem que estar vivo para o filho terminar sem virar zumbi
    printf("PAI - terminei\n");
  }
  else if (pid == 0) { // PROCESSO FILHO
    printf("FILHO - eu sou o FILHO PID(%d). Vou esperar %ds...\n", getpid(), seconds);
    sleep(seconds);
    printf("FILHO - terminei\n");
    printf("FILHO - mas por que não me mataram?");
    exit(0);
  }

  return 0;
}
