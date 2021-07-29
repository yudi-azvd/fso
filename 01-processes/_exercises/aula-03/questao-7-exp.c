#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
  int i; pid_t pid;

  pid = fork(); 
  pid = fork(); 
  pid = fork(); 

  printf("questao 7 exp\n");

  return 0;
}