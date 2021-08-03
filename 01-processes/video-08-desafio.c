#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#define NGRANDCHILDREN 2

pid_t child;
pid_t grandchildren[NGRANDCHILDREN];
int grandchilren_sigs[] = {SIGUSR1, SIGUSR2};
int is_gchild_1 = 0;
int is_gchild_2 = 0;
// tem que dividir em mais variáveis (uma pra cada gchild) se não houvesse um delay de 4s para o gchild2
int child_received_sigterm_count = 0;
int gchild_receiveid_sigint = 0;
int parent_received_sigint = 0;


void grandchild_do(int sig) {
  if (sig == SIGUSR1) {
    printf("    (%d) gchild 1\n", getpid());
  }
  else if (sig == SIGUSR2) {
    printf("    (%d) gchild 2, my parent %d\n", getpid(), getppid());
  }
  else if (sig == SIGINT) {
    gchild_receiveid_sigint = 1;
    if (is_gchild_1) {
      printf("    (%d) gchild sending SIGTERM to (%d)\n", getpid(), getppid());
      kill(getppid(), SIGTERM);
    }
    else if (is_gchild_2) {
      sleep(4);
      printf("    (%d) gchild sending SIGTERM to (%d)\n", getpid(), getppid());
      kill(getppid(), SIGTERM);
    }
  }
}


int get_grandchild_index(int sig) {
  int i = 0;
  while (i < NGRANDCHILDREN) {
    if (grandchilren_sigs[i] == sig)
      return i;
    ++i;
  }
  return -1;
}


void child_send_sigterm_up(int sig) {
  ++child_received_sigterm_count;
  printf("  (%d) child received SIGTERM: %d\n", getpid(), child_received_sigterm_count);

  if (child_received_sigterm_count == NGRANDCHILDREN) {
    printf("  (%d) child sending SIGTERM to PARENT %d\n", getpid(), getppid());
    wait(NULL);
    sleep(1);
    wait(NULL);
    kill(getppid(), SIGTERM);
    exit(0);
  }
}


void child_send_sigint_down(int sig) {
  int i;
  signal(SIGTERM, child_send_sigterm_up);
  printf("  (%d) installed SIGTERM handler: %d\n", getpid(), getppid());
  for (i = 0; i < NGRANDCHILDREN; ++i) {
    printf("  (%d) child sending SIGINT down to gchild(%d)\n", getpid(), grandchildren[i]);
    kill(grandchildren[i], SIGINT);
  }
  printf("  (%d) child finished sending SIGINT down\n", getpid());
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
  if (sig == SIGINT)
    parent_received_sigint = 1;
  kill(child, sig);
}


void parent_say_goodbye(int sig) {
  printf("\n(%d) Goodbye...                      %d\n", getpid(), sig);
  exit(0);
}

// watch -n 1 'ps -x --forest | grep a.out | grep -v grep'
// mas ele ainda morre com quando se dá o comando pkill -f a.out
// https://unix.stackexchange.com/questions/318859/how-to-use-watch-command-with-a-piped-chain-of-commands-programs
int main() {
  int i;

  child = fork();

  if (child > 0) {
    printf("(%d) parent\n", getpid());
    signal(SIGUSR1, parent_send_sig_down);
    signal(SIGUSR2, parent_send_sig_down);
    signal(SIGINT, parent_send_sig_down);
    signal(SIGTERM, parent_say_goodbye);

    while (!parent_received_sigint) {
      pause();
    }

    printf("(%d) parent received SIGINT\n", getpid());
    while (1) {
      pause();
    }
  }

  if (child == 0) {
    printf("  (%d) my parent: %d\n", getpid(), getppid());
    signal(SIGINT, child_send_sigint_down);

    for (i = 0; i < NGRANDCHILDREN; ++i) {
      grandchildren[i] = fork();

      if (grandchildren[i] > 0) {
        // printf("  (%d) gchild %d created\n", getpid(), i+1);
        // setup child for this grandchild
        // signal(grandchildren[i], alguma função) ?      // signal(grandchildren[i], alguma função) ?
        signal(grandchilren_sigs[i], child_send_sig_down);
      }

      if (grandchildren[i] == 0) {
        printf("    (%d) my parent: %d\n", getpid(), getppid());
        signal(SIGUSR1, grandchild_do);
        signal(SIGUSR2, grandchild_do);
        signal(SIGINT, grandchild_do);
        if (i == 0)
          is_gchild_1 = 1;
        else if (i == 1)
          is_gchild_2 = 1;
        // install function for gchild i (um vetor de funções)
        while (!gchild_receiveid_sigint)
          pause();
        
        printf("    (%d) grandchild exiting\n", getpid());
        exit(0);
      }
    }

    // signal(SIGTERM, child_send_sigterm_up);
    // printf("  (%d) installed SIGTERM handler: %d\n", getpid(), getppid());

    // printf("  (%d) child on pause", getpid());
    while (1)
      pause();
    printf("  (%d) child exiting\n", getpid());
    exit(0);
  }
  
  return 0;
}
