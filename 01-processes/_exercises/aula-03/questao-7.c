#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

/*
1. **Quantos processos são criados por este programa? Justifique.**
4 iterações
processos = 2^4-1
-1 por que o processo pai imprime uma vez

2. **Quantas vezes é apresentado "FSO"? Justifique.**
2^4 = 16
*/

int main() {
  int i;
  pid_t pid;

  for (i = 0; i < 4; i++)
    pid = fork(); 
  
  printf("FSO\n");
  return 0;
}