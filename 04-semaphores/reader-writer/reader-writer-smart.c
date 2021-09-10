#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_READERS 4
#define MAX_WRITERS 2

int shared_data, readers_in_shared_mem;

sem_t mutex;
sem_t readers_in_shared_mem_mutex;

void sleep_random(int dt) {
  sleep(random() % dt);
  usleep(random() % 1000000);
}

void* read_data(void* _id) {
  int id = *((int*) _id);

  while (1) {
    sem_wait(&readers_in_shared_mem_mutex);
    if (readers_in_shared_mem == 0)
      sem_wait(&mutex);
    ++readers_in_shared_mem;
    sem_post(&readers_in_shared_mem_mutex);

    printf("R%0d read %d (%d readers)\n", id, shared_data, readers_in_shared_mem);
    sleep_random(2);

    printf("R%0d out\n", id);

    sem_wait(&readers_in_shared_mem_mutex);
    --readers_in_shared_mem;
    if (readers_in_shared_mem == 0) 
      sem_post(&mutex);
    sem_post(&readers_in_shared_mem_mutex);

    sleep_random(2);
  }
}

void* write_data(void* _id) {
  int id = *((int*) _id);

  while (1) {
    sem_wait(&mutex);

    if (readers_in_shared_mem != 0) {
      printf("ERROR > W %d: %d readers in shared mem\n", id, readers_in_shared_mem);
      exit(1);
    }

    shared_data = rand() % 256;
    printf("\t\t\tW%0d wrote %d (%d readers)\n", id, shared_data, readers_in_shared_mem);
    sleep_random(2);
    
    printf("\t\t\tW%0d leaving\n", id);
    sem_post(&mutex);
    printf("\t\t\tW%0d out\n", id);

    sleep_random(2);
  }
}

int main() {
  int i;
  pthread_t readers[MAX_READERS];
  pthread_t writers[MAX_WRITERS];

  sem_init(&mutex, 0, 1);
  sem_init(&readers_in_shared_mem_mutex, 0, 1);
  shared_data = 0;
  readers_in_shared_mem = 0;

  for ( i = 0; i < MAX_WRITERS; i++)
    pthread_create(&writers[i], NULL, &write_data, &i);
  
  for ( i = 0; i < MAX_READERS; i++)
    pthread_create(&readers[i], NULL, &read_data, &i);
  
  pthread_exit(NULL);
  return 0;
}