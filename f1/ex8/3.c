#include <stdio.h>
#include <stdlib.h>

int *f() {
  int *x = (int *)malloc(sizeof(int));
  *x = 100;
  return x;
}

int main() {
  int *x = f();
  printf("x mem address: %p\nx value: %d\n", x, *x);
  free(x);
  return 0;
}
