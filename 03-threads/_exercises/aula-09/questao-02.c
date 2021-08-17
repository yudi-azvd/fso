#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>


typedef struct user_t {
  int number;
  char name[20];
  char addr[20];
} user_t;


void* print_user(void *uinfo) {
  user_t* u = (user_t*) uinfo;
  printf("--- user: %d\n", u->number);
  printf("%s\n", u->name);
  printf("%s\n\n", u->addr);
  return NULL;
}


#define MAX_USERS 5

int main() {
  int i;
  pthread_t threads[MAX_USERS];
  user_t users[MAX_USERS] = {
    {20, "Yudi Yamane", "Jardins Mang."},
    {22, "Silvester Sta", "USA"},
    {50, "Jackie Chan", "Jardins Mang."},
    {100, "Grace Hopper", "NASA"},
    {25, "Fa Mulan", "China"},
  };

  for (i = 0; i < MAX_USERS; i++) {
    pthread_create(&threads[i], NULL, &print_user, (void*) &users[i]);
    sleep(1);
  }

  for (i = 0; i < MAX_USERS; i++) {
    pthread_join(threads[i], NULL);
  }

  return 0;
}
