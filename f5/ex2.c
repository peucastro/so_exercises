#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  for (int i = 0; i < 4; i++)
    fork();

  printf("pid = %d\n", getpid());

  exit(EXIT_SUCCESS);
}
