#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>


// void grandchild_print(int in) {
//   printf("(%d) my parent (%d)\n", getpid(), getppid());
// }

// void grandchild_send_sig_back_and_die(int sig) {
//   printf("(%d) send sig back and die\n", getpid());
// }

// void grandchild_setup(int sig) {
//   signal(sig, grandchild_print);
//   signal(SIGINT, grandchild_send_sig_back_and_die);
// }

// void child_setup() {
//   signal(SIGUSR1, );
// }

#define NGRANDCHILDREN 2

pid_t child;
pid_t grandchildren[NGRANDCHILDREN];
int grandchilren_sigs[] = {SIGUSR1, SIGUSR2};

int parent_received_sigint = 0;

int get_grandchild_index(int sig) {
  int i = 0;
  while (i < NGRANDCHILDREN) {
    if (grandchilren_sigs[i] == sig)
      return i;
    ++i;
  }
  return -1;
}


void child_send_sig_down(int sig) {
  int gchild_index = get_grandchild_index(sig); // aqui seria um dicionário.
  if (gchild_index == -1) {
    printf("  (%d) child: gchild signal not found %d\n", getpid(), sig);
    kill(getppid(), SIGTERM);
    exit(-1);
  }

  printf("  (%d) child sending %d down to (%d)\n", getpid(), sig, grandchildren[gchild_index]);
  kill(grandchildren[gchild_index], sig);
}

void parent_send_sig_down(int sig) {
  printf("\n(%d) parent sending down %d\n", getpid(), sig);
  // if (sig == SIGINT)
  //   parent_received_sigint = 1;
  kill(child, sig);
}

void parent_tear_down(int sig) {
  printf("\n(%d) Goodbye...                      %d\n", getpid(), sig);
  exit(0);
}


int main() {
  int i;

  child = fork();

  if (child > 0) {
    printf("(%d) I AM WHO I AM (not actually though)\n", getpid());
    signal(SIGUSR1, parent_send_sig_down);
    signal(SIGUSR2, parent_send_sig_down);
    signal(SIGINT, parent_send_sig_down);
    signal(SIGTERM, parent_tear_down);

    while (!parent_received_sigint) {
      pause();
    }
  }

  if (child == 0) {
    printf("  (%d) my parent: %d\n", getpid(), getppid());
    // signal(SIGUSR2, child_send_sig_down);

    for (i = 0; i < NGRANDCHILDREN; ++i) {
      grandchildren[i] = fork();

      if (grandchildren[i] > 0) {
        // setup child for this grandchild
        // signal(grandchildren[i], alguma função) ?
        signal(grandchilren_sigs[i], child_send_sig_down);
      }

      if (grandchildren[i] == 0) {
        printf("    (%d) my parent: %d\n", getpid(), getppid());
        // grandchild_setup(grandchilren_sigs[i]);
        while (1)
          pause();
        
        printf("    (%d) grandchild exiting\n", getpid());
        exit(0);
      }
    }

    // printf("  (%d) child on pause", getpid());
    while (1)
      pause();
    printf("  (%d) child exiting\n", getpid());
    exit(0);
  }
  
  return 0;
}
