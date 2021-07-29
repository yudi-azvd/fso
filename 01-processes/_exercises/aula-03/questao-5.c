#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


// Quantos processos esse programa gera? R: 3


// olhar ./questao-5-process-tree.png

// ./a.out & ps -x --forest
// ./a.out & ps -x --forest | grep './a.out' | sed -E 's/.*[0-9]+\s+.\s+//g' > tmp;code tmp

// .*\d+:\d+\s+.\s+ funciona no https://regex101.com/
int main() {
  pid_t a = fork();
  pid_t b = fork();

  printf("sistemas operacionais\n");
  return 0;
}