#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


// ./a.out 5
int main(int argc, char** argv) {
  int seconds = atoi(argv[1]);
  pid_t pid = fork();

  if (pid > 0) { // PROCESSO PAI
    printf("PAI - sou o pai. meu filho é %d\n", pid);
    printf("PAI - tô esperando meu filho terminar...\n");
    wait(NULL);
    printf("PAI - terminei logo depois do meu filho\n");
  }
  else if (pid == 0) { // PROCESSO FILHO
    printf("FILHO - eu sou o FILHO. me mandaram esperar %d segundos\n", seconds);
    printf("FILHO - ...\n");
    sleep(seconds);
    printf("FILHO - terminei\n");
  }

  return 0;
}