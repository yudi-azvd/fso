#include <stdio.h>
#include <stdlib.h>

// https://moj.naquadah.com.br/cgi-bin/contest.sh/bcr-FSO-2021_1-threads
// https://moj.naquadah.com.br/contests/bcr-FSO-2021_1-threads/butters-cracker-sequencial.html
// https://moj.naquadah.com.br/contests/bcr-FSO-2021_1-threads/butters-cracker-sequencial.pdf

int main(void) {
  int semente;
  
  printf("Digite a sua semente:\n");
  scanf("%d",&semente);

  for(int i=0;i<3;i++)
    printf("%d\n",rand_r(&semente)%256);
}