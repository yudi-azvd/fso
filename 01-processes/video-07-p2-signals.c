#include <stdio.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>


void handle_signal(int sig) {
  printf("CHILD(%d)> received signal %d\n", getpid(), sig);
  signal(SIGINT, handle_signal); // reinstall handler
  exit(0);
}


int main() {
  pid_t child_pid = fork();

  if (child_pid > 0) {
    printf("PARENT(%d)> my child(%d)\n", getpid(), child_pid);
    sleep(5);
    kill(child_pid, SIGKILL);
  }
  else if (child_pid == 0) {
    printf("CHILD(%d)> my parent(%d)\n", getpid(), getppid());
    sleep(10);
    signal(SIGKILL, handle_signal); // install hendler for the 1st time
  }

  return 0;
}