#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

#define SIZE 1000

int data[SIZE] = { [0 ... SIZE-1] = 1 };
int result[SIZE];


void child_do_nothing(int sig) { return; }


void calc_and_print_range(int start, int end) {
  int i;
  // printf("start %d, end %d\n", start, end);
  for (i = start; i < end; i++) {
    result[i] = data[i]*4+20;
    // printf("%d %d (%d) -- ", data[i]*4+20, result[i], i);
    printf("%d ", result[i]);
  }
  result[i] = data[i]*4+20;
  printf("%d\n\n", result[i]);
}


void init_data() {
  int i;
  for (i = 0; i < SIZE; i++)
    data[i] = i;
}


// exercpicio 8
// https://www.brunoribas.com.br/so/2021-1/#orgb5ea29f
int main() {
  init_data();
  pid_t pid = fork();

  if (pid > 0 ) {
    printf("(%d) parent\n", getpid());
    calc_and_print_range(0, SIZE/2-1);
    kill(pid, SIGINT);
  }
  
  if (pid == 0) {
    signal(SIGINT, child_do_nothing);
    pause();
    printf("  (%d) child\n", getpid());
    calc_and_print_range(SIZE/2, SIZE-1);
  }

  sleep(2);
  
  return 0;
}
