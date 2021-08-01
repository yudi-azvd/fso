#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// ./a.out & ps -x --forest
// ./a.out & ps -x --forest | grep './a.out' | sed -E 's/.*[0-9]+\s+.\s+//g' > tmp;code tmp


void print_many_times() {
  int i;
  for (i = 0; i < 1000; i++) {
    printf("(%d) hey\n", getpid());
  }
}


int main() {
  int i;
  const int nproc = 4;
  pid_t pids[nproc];

  for (i = 0; i < nproc; i++) {

    pids[i] = fork();

    if (pids[i] == 0) {
      printf("i = %d (%d) child, my parent (%d)\n", i, getpid(), getppid());
      // print_many_times();
      // break; // 
      exit(0); // se quiser acabar o programa de vez;
    }
  }
  
  sleep(2);
  return 0;
}