#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>

void handle_signal(int);

#define STR_MAX_LEN 11

// A linha na entrada padrão possuirá uma única string s de comprimento máximo de 10 caracteres
char cams[16][STR_MAX_LEN];
char name[STR_MAX_LEN];


/**
 * É o mesmo problema do flau.c. O que muda
 * é que reverso.c envia o sinal SIGALRM para o 
 * processo pai quando há um erro de câmera.
 * 
 * Por causa disso, dá pra usar os arquivos flau-x.in
 * para testar reverso.c. 
 */
int main() {
  signal(SIGINT, handle_signal);
  signal(SIGUSR1, handle_signal);
  signal(SIGUSR2, handle_signal);
  signal(SIGTERM, handle_signal);
  signal(SIGALRM, handle_signal);

  strcpy(cams[SIGUSR1], "Igor3k");
  strcpy(cams[SIGUSR2], "Monark");
  strcpy(cams[SIGINT], "Con1");
  strcpy(cams[SIGTERM], "Con2");
  strcpy(cams[SIGALRM], "Silencio");

  while (1) {
    pause();
  }

  return 0;
}


void handle_signal(int sig) {
  if (scanf("%s", name) == EOF)
    exit(0);

  if (strcmp(cams[sig], name) == 0) {
    printf("Certo\n");
  }
  else {
    printf("Erro\n");
    kill(getppid(), SIGALRM);
  }
}