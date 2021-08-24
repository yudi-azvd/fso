#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>

// Figure 31.6: A Parent Waiting For Its Child
// https://pages.cs.wisc.edu/~remzi/OSTEP/threads-sema.pdf


sem_t s;

void* child(void* arg) {
  printf("child\n");
  sem_post(&s);
  return NULL;
}


// gcc sem.c -pthread
int main() {
  int X = 0;
  sem_init(&s, 0, X);
  printf("parent: begin\n");
  pthread_t c;
  pthread_create(&c, NULL, child, NULL);
  sem_wait(&s);
  printf("parent: end\n");
  return 0;
}