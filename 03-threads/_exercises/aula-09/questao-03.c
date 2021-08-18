#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>


#define MAX_THREADS 2
#define ARR_SIZE 1200


typedef struct data_t {
  int begin;
  int end;
  int* results;
} data_t;


void* do_the_thing(void *d) {
  int i;
  data_t data = *((data_t*) d);
  for (i = data.begin; i <= data.end; i++) {
    data.results[i] = i*4 + 20;
  }
  
  return NULL;
}

void print_arr(int* arr, int size) {
  int i = 0;
  for (; i < size-1; i++) {
    printf("%d ", arr[i]);
  }
  printf("%d\n", arr[i]);
}


int main() {
  int i;
  int results[ARR_SIZE] = { [0 ... ARR_SIZE-1] = 0 };
  pthread_t threads[MAX_THREADS];
  data_t datas[MAX_THREADS];

  for (i = 0; i < MAX_THREADS; i++) {
    datas[i].results = results;
    datas[i].begin = i*400;
    datas[i].end = datas[i].begin + 400 - 1;
    printf("begin %d\n", datas[i].begin);
    printf("end   %d\n", datas[i].end  );
    pthread_create(&threads[i], NULL, &do_the_thing, &datas[i]);
  }
  data_t data;
  data.begin = i*400;
  data.end = data.begin + 400 - 1;
  data.results = results;
  printf("i = %d\n", i);
  printf("begin %d\n", data.begin);
  printf("end   %d\n", data.end  );
  do_the_thing(&data);

  for (i = 0; i < MAX_THREADS; i++) {
    pthread_join(threads[i], NULL);
  }

  print_arr(results, ARR_SIZE);

  return 0;
}
