#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

// fonte:
// https://stackoverflow.com/questions/25172425/create-zombie-process

int main() {
  pid_t pid;
  int status;

  pid = fork();
  if (pid < 0) { //erro
    perror("fork");
    exit(1);
  }
  else if (pid == 0) // filho
    exit(0);


  // pai
  sleep(10);

  printf("PAI inicialmente com PID %d\n", pid);
  pid = wait(&status);

  if (WIFEXITED(status))  
    fprintf(stderr, 
      "\n\t[%d]\tProcess %d exited with status %d\n",
      getpid(), pid, WEXITSTATUS(status));

  return 0;
}