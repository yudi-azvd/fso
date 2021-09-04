// https://moj.naquadah.com.br/cgi-bin/contest.sh/bcr-FSO-2021_1-threads
// https://moj.naquadah.com.br/contests/bcr-FSO-2021_1-threads/quaseprimos-threads.html

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>


typedef struct thread_data_t {
  int n;
  int result;
} thread_data_t;


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
  data->result = get_almost_prime_number_from(data->n);
}

int main() {
  int ntest_cases, number;
  pthread_t thread1, thread2;
  thread_data_t data1, data2;

  scanf("%d", &ntest_cases);

  while (1) {
    if (scanf("%d", &number) == EOF) break;
    data1.n = number;
    pthread_create(&thread1, NULL, &calc, &data1);

    if (scanf("%d", &number) == EOF) break;
    data2.n = number;
    pthread_create(&thread2, NULL, &calc, &data2);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("%d\n", data1.n);
    printf("%d\n", data2.n);
  }
}