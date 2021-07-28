#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


// Quantos processos esse programa gera?
int main() {
  pid_t a = fork();
  pid_t b = fork();

  printf("sistemas operacionais\n");
  return 0;
}