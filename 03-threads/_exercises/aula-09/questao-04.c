#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>


#define MAX_THREADS 5
#define ARR_SIZE 1000


typedef struct data_t {
  int found;
  int to_find;
  int ieth_thread;
  int* arr;
} data_t;


void print_data(data_t d) {
  printf("ieth_thread: %d\n", d.ieth_thread);
  printf("        arr: %p\n\n", d.arr);
}


void* threaded_search(void *d) {
  data_t* data = ((data_t*) d);
  int i, interval_size = ARR_SIZE / MAX_THREADS;
  int start = data->ieth_thread*interval_size;
  int end = start + interval_size - 1;

  // printf("start: %d\n", start);
  // printf("  end: %d\n\n", end);

  for (i = start; i <= end; i++) {
    if (data->arr[i] == data->to_find) {
      data->found = data->ieth_thread+1;
      printf("thread(%d) found at arr[%d]\n", data->ieth_thread, i);
    }
  }
  
  return NULL;
}

void init_arr(int* arr, int size) {
  int i = 0;
  for (; i < size; i++) {
    arr[i] = i;
  }
}

void print_arr(int* arr, int size) {
  int i = 0;
  for (; i < size-1; i++) {
    printf("%d ", arr[i]);
  }
  printf("%d\n", arr[i]);
}

// gcc questao-04.c
// ./a.out 500
int main(int argc, char** argv) {
  int i, start, end, to_find = atoi(argv[1]);
  int arr[ARR_SIZE];
  pthread_t threads[MAX_THREADS];
  data_t datas[MAX_THREADS];

  init_arr(arr, ARR_SIZE);
  int interval_size = ARR_SIZE / MAX_THREADS;

  for (i = 0; i < MAX_THREADS; i++) {
    datas[i].arr = arr;
    datas[i].ieth_thread = i;
    datas[i].found = 0;
    datas[i].to_find = to_find;
    pthread_create(&threads[i], NULL, &threaded_search, &datas[i]);
  }

  for (i = 0; i < MAX_THREADS; i++) {
    pthread_join(threads[i], NULL);
  }

  return 0;
}
