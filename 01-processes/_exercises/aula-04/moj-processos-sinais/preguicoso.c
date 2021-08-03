#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>


// outra solução instalando um sinal a cada sinal:
// https://youtu.be/V3mTFMWTgao?t=292

int alarm_count = 0;

void handle_signal(int);

int main() {
  signal(SIGUSR1, handle_signal);
  signal(SIGALRM, handle_signal);

  while (1) {
    pause();
  }

  return 0;
}


void handle_signal(int new_sig) {
  if (new_sig == SIGUSR1) {
    printf("SIGUSR1 eh para aproveitar mais um pouco\n");
    return;
  }

  if (alarm_count+1 == 3) {
    printf("Os incomodados que se mudem, tchau\n");
    exit(0);
  }

  if (new_sig == SIGALRM) {
    printf("Ai que sono, quero dormir mais um pouco\n");
    ++alarm_count;
  }
}
