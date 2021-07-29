#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

#define SIGNALS_MAX_LEN 4

const int password_activation_seq[] = {SIGINT, SIGUSR2, SIGTERM};
const int ACTIVATION_COUNT = sizeof(password_activation_seq)/sizeof(int);
int password_index = 0;
int is_password_active = 0;

int signals[SIGNALS_MAX_LEN] = {0, 0, 0, 0};
int sig_index = 0;

void clear_signals();
void print_sig(int sig);
void handle_signal(int new_sig);

// SIGINT SIGUSR2 SIGTERM => Senha acionada
// SIGINT SIGUSR2 SIGTERM SIGUSR1 => Tchau

int main() {
  signal(SIGINT, handle_signal);
  signal(SIGUSR1, handle_signal);
  signal(SIGUSR2, handle_signal);
  signal(SIGTERM, handle_signal);

  while (1)
    pause();

  return 0;
}


void clear_signals() {
  int i = 0;
  for (; i < SIGNALS_MAX_LEN; i++) {
    signals[i] = -1;
  }
}

void print_sig(int sig) {
  printf("Recebi %d\n", sig);
}

void handle_signal(int new_sig) {
  print_sig(new_sig);

  int new_sig_matches_sig_at_password_index =
    new_sig == password_activation_seq[password_index];

  if (new_sig_matches_sig_at_password_index) {
    signals[sig_index++] = new_sig;
    password_index++;
    return;
  }

  if (!new_sig_matches_sig_at_password_index) {
    clear_signals();
    sig_index = 0;
    password_index = 0;
    is_password_active = 0;
    return;
  }

  int signals_matches_count = password_index+1;
  if (signals_matches_count == ACTIVATION_COUNT) {
    printf("Senha acionada\n");
    is_password_active = 1;
    return;
  }

  if (is_password_active && new_sig == SIGUSR1) {
    printf("Tchau\n");
    return;
  }

}
