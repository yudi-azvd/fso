#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#define NO_CHILD 1

pid_t child_pid = NO_CHILD;
int killed_zombie = 0;
int forked = 0;

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
  if (!forked) {
    // printf("(%d)\n", getpid());
    child_pid = fork();
    forked = 1;

    if (child_pid == 0) {
      // printf("  (%d)\n", getpid());
      exit(0);
    }
    return;
  }

  if (!killed_zombie && forked && child_pid > 0) {
    // printf("(%d) killing (%d)\n", getpid(), child_pid);
    wait(NULL);
    killed_zombie = 1;
    return;
  }

  if (killed_zombie && child_pid > 0) {
    // printf("(%d) finishing\n", getpid());
    exit(0);
  }
}