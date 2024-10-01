#include <stdio.h>

int* f() {
	int x = 100;
	return &x;
}

int main() {
	int *x = f();
	printf("x = %n\n", x);
	return 0;
}
