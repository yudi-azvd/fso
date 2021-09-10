#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_READERS 4
#define MAX_WRITERS 2

int shared_data;

sem_t mutex;

void sleep_random(int dt) {
  sleep(random() % dt);
  usleep(random() % 1000000);
}

void* read_data(void* _id) {
  int id = *((int*) _id);

  while (1) {
    sem_wait(&mutex);
    printf("R%0d read %d\n", id, shared_data);
    sleep_random(2);
    sem_post(&mutex);
    printf("R%0d out\n", id);

    sleep_random(2);
  }
}

void* write_data(void* _id) {
  int id = *((int*) _id);

  while (1) {
    sem_wait(&mutex);
    shared_data = rand() % 256;
    printf("\t\tW%0d wrote %d\n", id, shared_data);
    sleep_random(2);
    sem_post(&mutex);
    printf("\t\tW%0d out\n", id);

    sleep_random(2);
  }
}

int main() {
  int i;
  pthread_t readers[MAX_READERS];
  pthread_t writers[MAX_WRITERS];

  sem_init(&mutex, 0, 1);
  shared_data = 0;

  for ( i = 0; i < MAX_READERS; i++)
    pthread_create(&readers[i], NULL, &read_data, &i);
  
  for ( i = 0; i < MAX_WRITERS; i++)
    pthread_create(&writers[i], NULL, &write_data, &i);
  
  pthread_exit(NULL);
  return 0;
}