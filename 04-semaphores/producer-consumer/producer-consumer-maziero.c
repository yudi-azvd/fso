#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>

// Figure 31.10: Adding The Full And Empty Conditions
// https://pages.cs.wisc.edu/~remzi/OSTEP/threads-sema.pdf

// Ótima explicação
// http://pages.cs.wisc.edu/~bart/537/lecturenotes/s6.html

#define MAX_BUFFER 10
#define MAX_PROD 4
#define MAX_CONS 2

int empty_slots = MAX_BUFFER;
int items_in_buffer = 0;

sem_t cons_sem, prod_sem, mutex;

void sleep_random(int dt) {
  sleep(random() % dt);
  usleep(random() % 1000000);
}

/**
 * - produtor espera por um slot vazio pra colocar o item nele
 * - produtor consegue acesso à região crítica
 * - produtor produz e coloca item no buffer
 * - produtor libera   acesso à região crítica
 * - produtor sinaliza ao consumidor que tá na fila que tem item no buffer
 */ 
void* produce(void* id) {
  int tid = *((int*) id);
  
  while (1) {
    sem_wait(&prod_sem);
    sem_wait(&mutex);
      items_in_buffer++; empty_slots--;
      printf("P %0d | %d items, %d slots.\n", tid, items_in_buffer, empty_slots);
    sem_post(&mutex);
    sem_post(&cons_sem);

    sleep_random(2);
  } 
}

/**
 * - consumidor espera pela presença/produção de um item no buffer
 * - consumidor consegue acesso à região crítica
 * - consumidor consome
 * - consumidor libera   acesso à região crítica
 * - consumidor sinaliza produtor na fila que existe slot com espaço no buffer
 */ 
void* consume(void* id) {
  int tid = *((int*) id); 

  while (1) {
    sem_wait(&cons_sem);
    sem_wait(&mutex);
      items_in_buffer--; empty_slots++;
      printf("C %0d | %d items, %d slots.\n", tid, items_in_buffer, empty_slots);
    sem_post(&mutex);
    sem_post(&prod_sem);

    sleep_random(2);
  }
}

/**
 * Dependência cruzada entre consumimdor e produtor
 */
int main(int argc, char** argv) {
  pthread_t producers[MAX_PROD];
  pthread_t consumers[MAX_CONS];

  empty_slots = MAX_BUFFER;
  items_in_buffer = 0;
  sem_init(&cons_sem, 0, 0);
  sem_init(&prod_sem, 0, MAX_BUFFER);
  sem_init(&mutex, 0, 1);

  for (size_t i = 0; i < MAX_PROD; i++) {
    pthread_create(&producers[i], NULL, &produce, &i);
  }

  for (size_t i = 0; i < MAX_CONS; i++) {
    pthread_create(&consumers[i], NULL, &consume, &i);
  }

  pthread_exit(NULL);
}
