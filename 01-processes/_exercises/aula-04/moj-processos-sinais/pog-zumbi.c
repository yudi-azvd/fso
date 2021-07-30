// #include <stdio.h>
// #include <signal.h>
// #include <unistd.h>
// #include <stdlib.h>
// #include <sys/types.h>
// #include <sys/wait.h>

// #define NO_CHILD -1

// pid_t child_pid = NO_CHILD;
// int child_status = -1;
// int killed_zombie = 0;

// void handle_signal(int);

// int main() {
//   signal(SIGUSR1, handle_signal);
//   signal(SIGUSR2, handle_signal);

//   while (1) {
//     pause();
//   }

//   return 0;
// }


// void handle_signal(int sig) {
//   printf("(%d) | --- HANDLE SIGNAL ---\n", getpid());
//   printf("(%d) | child PID %d\n", getpid(), child_pid);

//   printf("(%d) | child_pid == NO_CHILD => %d\n", getpid(), child_pid == NO_CHILD);
//   printf("(%d) | child_pid >  0        => %d\n", getpid(), child_pid > 0);
//   printf("(%d) | child_pid == 0        => %d\n", getpid(), child_pid == 0);

//   if (child_pid == NO_CHILD) {
//     child_pid = fork();
//     printf("(%d) | child PID after fork: %d\n", getpid(), child_pid);
    
//     if (child_pid == 0) {
//       printf("  (%d) | turning into zombie...\n", getpid());
//       exit(0);
//     }

//     return;
//   }
//   else if (child_pid > 0) {
//     if (killed_zombie) {
//       exit(0);
//     }
//     wait(&child_status);
//     child_pid = NO_CHILD;
//     printf("(%d) | child PID %d after killing\n", getpid(), child_pid);
//     return;
//   }
// }
