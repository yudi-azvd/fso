#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// https://moj.naquadah.com.br/cgi-bin/contest.sh/bcr-FSO-2021_1-threads
// https://moj.naquadah.com.br/contests/bcr-FSO-2021_1-threads/butters-cracker-sequencial.html
// https://moj.naquadah.com.br/contests/bcr-FSO-2021_1-threads/butters-cracker-sequencial.pdf

/*
Exemplos para os casos de teste:
00.in
  ./a.out 1 5

01.in
  ./a.out 6 5

02.in
  ./a.out 928 10

03.in
  ./a.out 730 81
*/
int main(int argc, char** argv) {
  unsigned int semente = atoi(argv[1]);
  int rounds = atoi(argv[2]);
  
  for(int i = 0; i < rounds; i++) {
    for(int j = 1; j < 10000; j++)
      rand_r(&semente);
    printf("%d\n", rand_r(&semente) % 256);
  }
}