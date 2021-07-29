#include <stdio.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

// video 8: https://www.youtube.com/watch?v=X5EIF_i9lYM

// $(...) pega o PID do processo a.out
// outro jeito:

// Produz o resultado como o do professor
// pstree yudi -p | grep 'a.out' | sed -E 's/^(.+)a\.out\(([0-9]+)\)/\2/' | xargs kill -s USR1 | xclip -s clipboard
// kill -s USR1 $(pstree yudi -p | grep 'a.out' | sed -E 's/^(.+)a\.out\(([0-9]+)\)/\2/')

void handle_sigusr1(int sig) {

  printf("\nSIGUSR1: received signal %d\n\n", sig);
}

int keyboards_interrupts = 0;
void handle_keyboard_interrupt(int sig) {
  printf("\nSIGINT: received signal %d\n", sig);
  printf("keyboard interrupts %d/3\n", ++keyboards_interrupts);

  if (keyboards_interrupts == 3)
    exit(0);
  
  printf("\n");
}


  
int main() {
  signal(SIGUSR1, handle_sigusr1);
  signal(SIGINT, handle_keyboard_interrupt);

  printf("This process(%d) is running\n", getpid());
  printf("and waiting for signals...\n\n");
  while (1)
    pause();
  
  printf("This process(%d) finished gracefully\n", getpid());
  return 0;
}