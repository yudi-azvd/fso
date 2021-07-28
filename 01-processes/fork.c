#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  pid_t pid = fork();
  // tudo abaixo dessa linha é potecialmente o processo FILHO

  if (pid > 0) {
    sleep(4); // 10s
    printf("meu filho é %d\n", pid);
  }
  else if (pid == 0) {
    sleep(2); // 5s
    printf("eu sou o filho\n");
  }

  return 0;
}