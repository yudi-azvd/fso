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
  pid_t a = fork(), b;

  if (a > 0) {
    printf("i'm parent process (%d). my child is (%d)\n", getpid(), a);
    b = fork();
  }

  if (b > 0) {
    printf("i'm parent process (%d). my child is (%d)\n", getpid(), b);
  }

  if (a == 0) {
    printf("i'm child process (%d)\n", getpid());
  }

  if (b == 0) {
    printf("i'm child process (%d)\n", getpid());
  }

  printf("sistemas operacionais\n");
  sleep(5);
  return 0;
}