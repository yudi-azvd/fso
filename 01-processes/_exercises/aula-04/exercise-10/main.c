#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>


#define SIZE 1000

int data[SIZE] = { [0 ... SIZE-1] = 1 };


void child_do_nothing(int sig) { return; }


void init_data() {
  int i;
  for (i = 0; i < SIZE; i++)
    data[i] = i;
}

int search_in_range(int find, int start, int end) {
  int i;
  for (i = start; i <= end; i++)
    if (data[i] == find)
      return 1;
  return 0;
} 


// exercpicio 10
// https://www.brunoribas.com.br/so/2021-1/#orgb5ea29f
int main(int argc, char** argv) {
  init_data();
  int i, j, nchildren = 5, find = atoi(argv[1]);
  printf("searching for %d...\n", find);
  pid_t p;

  int start, end;
  int interval_size = SIZE / nchildren;
  int limit;
  for (i = 0; i < nchildren; i++) {
    p = fork();

    if (p == 0) {
      start = i * interval_size;
      end = start + interval_size-1;
      int found = search_in_range(find, start, end);
      printf("    (%d) searching in [%d,%d]\n", i+1, start, end);
      if (found) {
        exit(i+1);
      }
      exit(0);
    }
  }

  sleep(3); // pra dar tempo de todos os filhos imprimirem
  i = nchildren;
  int status;
  while (i--) {
    wait(&status);
    int s = WEXITSTATUS(status);
    if (s != 0)
      printf("process %d found it\n", s);
  }
  return 0;
}
