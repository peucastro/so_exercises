#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  char *p = strdup(argv[1]);
  int count = 0;

  for (int i = 2; i < argc; i++)
    if (strcmp(p, argv[i]) == 0)
      count++;

  printf("%s occours in the second string %d times!\n", p, count);
  return 0;
}
