#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

#define SIGNALS_MAX_LEN 4

const int correct_signal_sequence[] = {SIGINT, SIGUSR2, SIGTERM, SIGUSR1};
// são necessários apenas os 3 primeiros sinais na ordem para ativação
const int ACTIVATION_THRESHOLD = sizeof(correct_signal_sequence)/sizeof(int)-1;
int signals[SIGNALS_MAX_LEN] = {-1, -1, -1, -1};
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

  while (1) {
    pause();
  }

  return 0;
}


void print_curr_signals() {
  int i = 0;
  printf("signals: [");
  for (; i < sig_index-1; i++) {
    printf("%d ", signals[i]);
  }
  printf("%d]\n", signals[i]);
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

// Manda `-exec signal SIGINT` no painel do debugger
void handle_signal(int new_sig) {
  print_sig(new_sig);

  int new_sig_matches_sig_at_seq_index =
    new_sig == correct_signal_sequence[sig_index];

  if (new_sig_matches_sig_at_seq_index) {
    signals[sig_index++] = new_sig;

    if (sig_index == ACTIVATION_THRESHOLD) {
      printf("Senha acionada\n");
      return;
    }

    if (sig_index == ACTIVATION_THRESHOLD+1 && new_sig == SIGUSR1) {
      printf("Tchau\n");
      exit(0);
    }
    
    return;
  }

  if (!new_sig_matches_sig_at_seq_index) {
    clear_signals();
    sig_index = 0;

    // GAMBIARRA?: recomeçar sequencia quando new_signal=SIGINT vei na hora errada
    // repetido? parece iqual à linha 64
    if (new_sig == SIGINT)
      signals[sig_index++] = new_sig;
    return;
  }
}
