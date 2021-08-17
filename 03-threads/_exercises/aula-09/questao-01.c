#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

void* print_name(void *name) {
  printf("%s\n", (char*) name);
  sleep(1);

  return NULL;
}

int main() {
  pthread_t tid1, tid2;
  char* firstname = "Yudi";
  char* lastname = "Yamane";
  pthread_create(&tid1, NULL, &print_name, (void*) firstname);
  sleep(1);
  pthread_create(&tid2, NULL, &print_name, (void*) lastname);
  sleep(2);
  return 0;
}
