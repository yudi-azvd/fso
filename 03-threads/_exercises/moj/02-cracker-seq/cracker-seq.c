#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

// https://moj.naquadah.com.br/cgi-bin/contest.sh/bcr-FSO-2021_1-threads
// https://moj.naquadah.com.br/contests/bcr-FSO-2021_1-threads/butters-cracker-sequencial.html
// https://moj.naquadah.com.br/contests/bcr-FSO-2021_1-threads/butters-cracker-sequencial.pdf

// Valgrind
// https://github.com/microsoft/vscode-cpptools/issues/4531


#define MAX 1000
// #define MAX 2

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

int find_seed(int*numbers, int size, int min_seed, int max_seed) {
  unsigned int seed = min_seed;

  while (seed <= max_seed) {
    if (is_correct_seed(numbers, size, seed))
      return seed;
    ++seed;
  }

  return -1;
}

int main() {
  int i, min_seed, max_seed, rand_number_mod_256;
  int size = 0, capacity = MAX;
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