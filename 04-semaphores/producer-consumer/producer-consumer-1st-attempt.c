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

#define MAX 100

int fill = 0;
int use  = 0;
int buffer[MAX];

void put(int value) {
  buffer[fill] = value;
  fill = (fill + 1) % MAX;
}

int get() {
  int tmp = buffer[use];
  use = (use + 1) % MAX;
  return tmp;
}

sem_t empty, full;

void* producer(void* arg) {
  int i = 0, loops = 100;
  
  for (; i < loops; ++i) {
    sem_wait(&empty);
    put(i);
    sem_post(&full);
  } 
}

void* consumer(void* arg) {
  int tmp = 0;
  while (tmp != -1) {
    sem_wait(&full);
    tmp = get();
    sem_post(&empty);
    printf("%d\n", tmp);
  }
}

int main(int argc, char** argv) {
  // ...
  sem_init(&empty, 0, MAX);
  sem_init(&full, 0, 0);
  // ...
}


int main() {
  
}