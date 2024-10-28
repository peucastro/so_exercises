#include <stdio.h>

void g(int *x) {
  *x += 100;
  printf("g: %d\n", *x);
}

void f() {
  int x = 400;
  printf("f: %d\n", x);
  g(&x);
}

int main() {
  f();
  return 0;
}
