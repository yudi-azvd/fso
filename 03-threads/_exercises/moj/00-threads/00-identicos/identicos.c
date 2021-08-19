#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>


// https://www.brunoribas.com.br/so/2021-1/#orga52554a

int cmpint(const void* a, const void* b) {
  return *((int*)a) - *((int*)b);
}

int n;

void* threaded_sort(void* v) {
  int* arr = (int*) v;

  qsort(arr, n, sizeof(int), cmpint);
  return NULL;
}


void read_arr(int* arr, int n) {
  int i = 0;
  for (; i < n; i++)
    scanf("%d", &arr[i]);
  
}

void print_arr(int* arr, int size) {
  int i = 0;
  for (; i < size-1; i++) {
    printf("%d ", arr[i]);
  }
  printf("%d\n", arr[i]);
}


int cmparr(int* arr1, int* arr2, int n) {
  int i = 0;
  for (; i < n; i++)
    if (arr1[i] != arr2[i])
      return 0;
  return 1;
}


#define ARR_SIZE 10000000
// #define ARR_SIZE 1000

// original stack size 8192
int main() {
  int i;
  int arr1[ARR_SIZE];
  int arr2[ARR_SIZE];
  pthread_t threads[2];

  scanf("%d\n", &n);
  read_arr(arr1, n);
  read_arr(arr2, n);

  pthread_create(&threads[0], NULL, &threaded_sort, arr1);
  pthread_create(&threads[1], NULL, &threaded_sort, arr2);

  pthread_join(threads[0], NULL);
  pthread_join(threads[1], NULL);

  if (cmparr(arr1, arr2, n) == 1)
    printf("Mesmos elementos\n");
  else
    printf("Diferentes\n");

  return 0;
}
