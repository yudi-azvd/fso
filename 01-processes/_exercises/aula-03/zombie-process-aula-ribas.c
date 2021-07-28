#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


// aula na minutagem
// https://youtu.be/7Ag2raA18bo?t=755
int main() {
  pid_t pid = fork();

  if (pid > 0) {
    printf("PAI - PID: %d\n", getpid());
  }
  else if (pid == 0) {
    printf("FILHO - PID: %d\n", getpid());
    exit(0);
    printf("FILHO - ainda vivo?\n");
  }
  else
    printf("ERRO no fork");
  
  sleep(50);
  return 0;
}