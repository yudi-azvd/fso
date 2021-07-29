#include <stdio.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

// $(...) pega o PID do processo a.out
// outro jeito:

// Produz o resultado como o do professor
// pstree yudi -p | grep 'a.out' | sed -E 's/^(.+)a\.out\(([0-9]+)\)/\2/' | xargs kill -s USR1 | xclip -s clipboard
// kill -s USR1 $(pstree yudi -p | grep 'a.out' | sed -E 's/^(.+)a\.out\(([0-9]+)\)/\2/')

void handle_signal(int sig) {
  printf("received signal %d\n", sig);
}


  
int main() {
  signal(SIGUSR1, handle_signal);

  printf("This process(%d) is running...\n", getpid());
  sleep(40);
  printf("This process(%d) finished gracefully\n", getpid());
  return 0;
}