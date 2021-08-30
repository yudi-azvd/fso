// https://moj.naquadah.com.br/cgi-bin/contest.sh/bcr-FSO-2021_1-threads
// https://moj.naquadah.com.br/contests/bcr-FSO-2021_1-threads/aleatorios-identicos.html


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#define SEEDS_CAPACITY (1<<17+1)
#define MAX_THREADS 4

typedef struct data_t {
  int to_find;
  int min_seed;
  int max_seed;
  int seeds[SEEDS_CAPACITY];
  int seeds_size;
} data_t;


void* do_in_range(void* d) {
  data_t* data = (data_t*) d;
  int curr_seed = data->min_seed, seed = 0, i, seeds_index = 0;
  int rounds = 100000;
  int rand_mod_8;

  for (; curr_seed <= data->max_seed; ++curr_seed) {
    seed = curr_seed;
    for (i = 0; i < rounds-1; ++i) {
      rand_r(&seed);
    }

    rand_mod_8 = rand_r(&seed) % 8;
    if (rand_mod_8 == data->to_find)
      data->seeds[seeds_index++] = curr_seed;
  }

  data->seeds_size = seeds_index;
  // printf("in thread [%d, %d]\n", data->min_seed, data->max_seed);
}


void print_data_seeds(data_t* datas, int size) {
  int i = 0, j;
  for (; i < size; i++) {
    for (j = 0; j < datas[i].seeds_size; j++) {
      printf("%d\n", datas[i].seeds[j]);
    }
  }
}


int main() {
  int i, min_seed, max_seed, rand_number_mod_256;
  int to_find, interval_size, rest, rest_adjustment = 0;
  pthread_t threads[MAX_THREADS];
  data_t datas[MAX_THREADS];

  scanf("%d %d %d", &min_seed, &max_seed, &to_find);
  interval_size = (max_seed - min_seed + 1) / MAX_THREADS;
  rest = (max_seed - min_seed + 1) % MAX_THREADS;
  if (rest != 0)
    rest_adjustment = -1;

  for (i = 0; i < MAX_THREADS+rest_adjustment; ++i) {
    datas[i].to_find = to_find;
    datas[i].min_seed = min_seed + i*interval_size;
    datas[i].max_seed = datas[i].min_seed + interval_size - 1;
    // printf("[%d, %d]\n", datas[i].min_seed, datas[i].max_seed);
    pthread_create(&threads[i], NULL, do_in_range, &datas[i]);
  }

  if (rest_adjustment == -1) {
    printf("rest i=%d\n", i);
    datas[i].to_find = to_find;
    datas[i].min_seed = min_seed + i*interval_size;
    datas[i].max_seed = max_seed;
    // printf("[%d, %d]\n", datas[i].min_seed, datas[i].max_seed);
    pthread_create(&threads[i], NULL, do_in_range, &datas[i]);
  }

  for (size_t i = 0; i < MAX_THREADS; i++)
    pthread_join(threads[i], NULL);

  print_data_seeds(datas, MAX_THREADS); 

  return 0;
}