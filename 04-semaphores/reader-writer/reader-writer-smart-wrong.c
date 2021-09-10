#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_READERS 4
#define MAX_WRITERS 2
#define TABS "\t\t\t\t"

#define C_RED     "\x1b[31m"
#define C_BLUE    "\x1b[34m"
#define C_GRAY    "\x1b[90m"
#define C_RESET   "\x1b[0m"

int shared_data, readers_in_shared_mem;

sem_t mutex;
sem_t readers_in_shared_mem_mutex;

void sleep_random(int dt) {
  sleep(random() % dt);
  usleep(random() % 1000000);
}

void* read_data(void* _id) {
  long id = (long) _id;

  while (1) {
    sem_wait(&readers_in_shared_mem_mutex);
    ++readers_in_shared_mem;
    if (readers_in_shared_mem == 1)
      sem_wait(&mutex);
    sem_post(&readers_in_shared_mem_mutex);

    printf("R%2ld read %d (%d readers)\n", id, shared_data, readers_in_shared_mem);
    sleep_random(2);

    printf("R%2ld out\n", id);

    sem_wait(&readers_in_shared_mem_mutex);
    --readers_in_shared_mem;
    if (readers_in_shared_mem == 0) 
      sem_post(&mutex);
    sem_post(&readers_in_shared_mem_mutex);

    sleep_random(2);
  }
}

void* write_data(void* _id) {
  long id = (long) _id;

  while (1) {
    sem_wait(&mutex);

    if (readers_in_shared_mem != 0) {
      printf("%sERROR > W %2ld: %d readers in shared mem\n", TABS, id, readers_in_shared_mem);
      exit(1);
    }

    shared_data = rand() % 256;
    printf("%sW%2ld wrote %d (%d readers)\n", TABS, id, shared_data, readers_in_shared_mem);
    sleep_random(2); 
  
    printf("%sW%2ld leaving\n", TABS, id);
    sem_post(&mutex);
    printf("%sW%2ld out\n", TABS, id);

    sleep_random(2);
  }
}


// Leitores podem entrar na região crítica enquanto um escritor
// está presente.
int main() {
  int i;
  pthread_t readers[MAX_READERS];
  pthread_t writers[MAX_WRITERS];
  printf(C_RESET "oi\n");

  sem_init(&mutex, 0, 1);
  sem_init(&readers_in_shared_mem_mutex, 0, 1);
  shared_data = 0;
  readers_in_shared_mem = 0;

  for ( i = 0; i < MAX_READERS; i++) {
    pthread_create(&readers[i], NULL, &read_data, (void*) i);
  }
  for ( i = 0; i < MAX_WRITERS; i++) {
    pthread_create(&writers[i], NULL, &write_data, (void*) i);
  }
  
  pthread_exit(NULL);
  return 0;
}