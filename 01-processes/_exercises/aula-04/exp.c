#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

// olhar ./exp-process-tree.png

// ./a.out & ps -x --forest
int main() {
  int i;
  pid_t pid1 = fork();
  pid_t pid2 = fork();

  printf("olar %d\n", getpid());

  sleep(6); //  tem que esperar tempo o suficiente
}