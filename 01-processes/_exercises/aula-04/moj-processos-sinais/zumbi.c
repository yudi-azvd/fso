#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#define NO_CHILD -1

pid_t child_pid = NO_CHILD;
int child_status = -1;
int killed_zombie = 0;

void handle_signal(int);

int main() {
  signal(SIGUSR1, handle_signal);
  signal(SIGUSR2, handle_signal);

  while (1) {
    pause();
  }

  return 0;
}


void handle_signal(int sig) {
  if (!killed_zombie) {
    child_pid = fork();
  }

  printf("(%d)\n", getpid());

  if (child_pid == 0) {
    exit(0);
  }

  if (child_pid > 0 && !killed_zombie) {
    wait(NULL);
    killed_zombie = 1;
    return;
  }

  if (child_pid > 0 && killed_zombie)
    exit(0);
}
