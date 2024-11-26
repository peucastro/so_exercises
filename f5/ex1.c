#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  fork();
  fork();
  fork();

  printf("pid = %d\n", getpid());

  exit(EXIT_SUCCESS);
}
