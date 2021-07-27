#include <stdio.h>
#include <stdlib.h>

// Não funciona como esperado:
// ./a.out abacaxi & ./a.out banana
int main(int argc, char** argv) {
  int i = 0;

  for (i = 0; i < 100; i++) {
    printf("%s\n", argv[1]);
  }
  
  return 0;
}