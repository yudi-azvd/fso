// https://moj.naquadah.com.br/cgi-bin/contest.sh/bcr-FSO-2021_1-threads
// https://moj.naquadah.com.br/contests/bcr-FSO-2021_1-threads/quaseprimos-threads.html

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>


#define SHOUTED_NUMBERS_CAPACITY 1000
#define MAX_THREADS 2


typedef struct thread_data_t {
  int size;
  int shouted_numbers[SHOUTED_NUMBERS_CAPACITY/2];
  long int almost_prime[SHOUTED_NUMBERS_CAPACITY/2];
} thread_data_t;


void print_shouted_numbers(thread_data_t* datas) {
  int i;
  for (i = 0; i < datas[0].size; ++i)
    printf("%d\n", datas[0].shouted_numbers[i]);
  for (i = 0; i < datas[1].size; ++i)
    printf("%d\n", datas[1].shouted_numbers[i]);
}

void print_almost_primes(thread_data_t* datas) {
  int i;
  for (i = 0; i < datas[0].size; ++i)
    printf("%ld\n", datas[0].almost_prime[i]);
  for (i = 0; i < datas[1].size; ++i)
    printf("%ld\n", datas[1].almost_prime[i]);
}

int has_more_than_10_divisors_greater_than_10_smaller_than_sqrt_of_n(int n) {
  double sqrt_n = sqrt(n);
  int divisors_count = 0;
  for (size_t divisor = 2; divisor < n; divisor++) {
    if (n % divisor == 0) {
      if (divisor <= 10)
        return 0;
      if (divisor < sqrt_n) {
        divisors_count++;
      }
    }
  }
  
  return divisors_count > 10;
}

int is_prime(int n) {
  for (size_t i = 2; i < n; i++) {
    if ((n % i) != 0)
      return 0;
  }
  
  return 1;
}

int get_almost_prime_number_from(int n) {
  while (1) {
    if (!is_prime(n) && has_more_than_10_divisors_greater_than_10_smaller_than_sqrt_of_n(n))
      return n;
    ++n;
  }

  return -1;
}

void* calc(void* d) {
  thread_data_t* data = (thread_data_t*) d;
  int almost_prime;
  for (size_t i = 0; i < data->size; i++) {
    data->almost_prime[i] = 
      get_almost_prime_number_from(data->shouted_numbers[i]);
  }
}

int main() {
  pthread_t threads[MAX_THREADS];
  thread_data_t datas[MAX_THREADS] = {[0 ... MAX_THREADS-1] = {0}};
  int shouted_numbers[SHOUTED_NUMBERS_CAPACITY];
  int i, ntest_cases = 0, number;

  scanf("%d", &ntest_cases);
  datas[0].size = ntest_cases/2;
  datas[1].size = ntest_cases/2;
  if (ntest_cases % MAX_THREADS != 0) 
    datas[1].size++;

  for (i = 0; i < datas[0].size; ++i)
    scanf("%d", &datas[0].shouted_numbers[i]);
  for (i = 0; i < datas[1].size; ++i)
    scanf("%d", &datas[1].shouted_numbers[i]);

  for (i = 0; i < MAX_THREADS; i++) {
    pthread_create(&threads[i], NULL, &calc, &datas[i]);
  }

  for ( i = 0; i < MAX_THREADS; i++) {
    pthread_join(threads[i], NULL);
  }

  // printf("%d\n", has_more_than_10_divisors_greater_than_10_smaller_than_sqrt_of_n(508079));
  // printf("%d\n", has_more_than_10_divisors_greater_than_10_smaller_than_sqrt_of_n(600457));
  // printf("%d\n", has_more_than_10_divisors_greater_than_10_smaller_than_sqrt_of_n(600457));
  // printf("%d\n", has_more_than_10_divisors_greater_than_10_smaller_than_sqrt_of_n(6533033));

  print_almost_primes(datas);
  // print_shouted_numbers(datas);
  // printf("%d\n", has_more_than_10_divisors_greater_than_10_smaller_than_sqrt_of_n(600457));
  // printf("%d\n", get_almost_prime_number_from(6530430));
  // printf("%d\n", get_almost_prime_number_from(550794));
}