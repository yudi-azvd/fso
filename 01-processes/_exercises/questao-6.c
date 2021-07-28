#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  pid_t pid_a = fork();
  pid_t pid_b;
  // printf("isso é impresso 4 vezes\n");

  if (pid_a > 0) { // PROCESSO PAI
    printf("PAI - sou o pai PID %d\n", getpid());

    pid_b = fork();
    if (pid_b == 0) { // 2o PROCESSO FILHO
      printf("FILHO - eu sou o 2o FILHO PID(%d)\n", getpid());
      sleep(1);
      exit(0);
    }

    sleep(3);
    exit(0);
  }
  
  if (pid_a == 0) { // 1o PROCESSO FILHO
    printf("FILHO - eu sou o 1o FILHO PID(%d)\n", getpid());
    sleep(1);
    exit(0);
  }

  return 0;
}
