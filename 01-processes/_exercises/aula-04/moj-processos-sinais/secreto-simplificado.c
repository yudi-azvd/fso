#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

// Foi visto em alguma aula de FSO aí

int password_index = 0;

// SIGINT SIGUSR2 SIGTERM => Senha acionada
// SIGINT SIGUSR2 SIGTERM SIGUSR1 => Tchau
void handle_signal(int sig) {
  printf("Recebi %d\n", sig);

  if (sig == SIGINT) {
    password_index = 1;
  }
  else if (password_index == 2 && sig == SIGUSR2) {
    password_index++;
  }
  else if (password_index == 3 && sig == SIGTERM) {
    password_index++;
    printf("Senha acionada");
  }
  else if (password_index == 4 && sig == SIGUSR2) {
    password_index++;
    printf("Tchau");
    exit(0);
  }
  else
    password_index = 0;
}


int main() {
  signal(SIGINT, handle_signal);
  signal(SIGUSR1, handle_signal);
  signal(SIGUSR2, handle_signal);
  signal(SIGTERM, handle_signal);

  while (1) {
    pause();
  }

  return 0;
}


