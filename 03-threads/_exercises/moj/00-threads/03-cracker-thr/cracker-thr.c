#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

// https://moj.naquadah.com.br/cgi-bin/contest.sh/bcr-FSO-2021_1-threads
// https://moj.naquadah.com.br/contests/bcr-FSO-2021_1-threads/butters-cracker-threads.html
// https://moj.naquadah.com.br/contests/bcr-FSO-2021_1-threads/butters-cracker-threads.pdf

// Valgrind
// https://github.com/microsoft/vscode-cpptools/issues/4531


#define INITIAL_CAPACITY 1000

int is_correct_seed(int* numbers, int size, unsigned int seed) {
  int i = 0, j, rand_mod_256, original_seed = seed;
  const int rounds = 10000;
  for (; i < size; i++) {
    for (j = 0; j < rounds-1; j++)
      rand_r(&seed);
    
    rand_mod_256 = rand_r(&seed) % 256;
    if (numbers[i] != rand_mod_256)
      return 0;
  }

  return 1;
}

typedef struct data_t {
  int* numbers;
  int size;
  unsigned int min_seed;
  unsigned int max_seed;
  unsigned int result_seed;
} data_t;

void* find_seed_in_range(void* d) {
  int seed;
  data_t* data = (data_t*) d;

  for (seed = data->min_seed; seed < data->max_seed; ++seed) {
    if (is_correct_seed(data->numbers, data->size, seed)) {
      data->result_seed = seed;
      return NULL;
    }
  }
  return NULL;
}

int find_seed(int* numbers, int size, const int min_seed, const int max_seed) {
  if (min_seed == max_seed) return min_seed;

  const unsigned int mid_seed = (min_seed+max_seed)/2;
  unsigned int seed1 = min_seed, seed2 = mid_seed;

  pthread_t threads[2];
  data_t datas[2] = {
    {numbers, size, min_seed, mid_seed, -1},
    {numbers, size, mid_seed+1, max_seed, -1},
  };

  pthread_create(&threads[0], NULL, &find_seed_in_range, &datas[0]);
  pthread_create(&threads[1], NULL, &find_seed_in_range, &datas[1]);

  pthread_join(threads[0], NULL);
  pthread_join(threads[0], NULL);

  if (datas[0].result_seed != -1)
    return datas[0].result_seed;
  else
    return datas[1].result_seed;

  return -1;
}

int main() {
  int i, min_seed, max_seed, rand_number_mod_256;
  int size = 0, capacity = INITIAL_CAPACITY;
  int* numbers = calloc(capacity, sizeof(int));
  
  scanf("%d %d", &min_seed, &max_seed);

  while (scanf("%d", &rand_number_mod_256) != EOF) {
    if (size+1 >= capacity) {
      capacity *= 2;
      numbers = realloc(numbers, capacity);
    }
    numbers[size++] = rand_number_mod_256;
  }

  unsigned int seed = find_seed(numbers, size, min_seed, max_seed);

  printf("%d\n", seed);

  free(numbers);
}