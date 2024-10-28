#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  char *p1 =
      (char *)malloc((strlen(argv[1]) + strlen(argv[2]) + 1) * sizeof(char));
  char *p2 = (char *)malloc(
      (strlen(argv[1]) + strlen(argv[2]) + strlen(argv[2]) + 1) * sizeof(char));

  int result = strcmp(argv[1], argv[2]);
  if (result == 0)
    printf("the strings are the same\n");
  else if (result < 0)
    printf("%s < %s\n", argv[1], argv[2]);
  else
    printf("%s > %s\n", argv[1], argv[2]);

  strcpy(p1, argv[1]);
  strcpy(p2, argv[2]);
  printf("p1 holds:%s\n", p1);
  printf("p2 holds:%s\n", p2);
  strcat(p1, p2);
  printf("p1 holds:%s\n", p1);
  strcat(p2, p1);
  printf("p2 holds:%s\n", p2);

  exit(EXIT_SUCCESS);
}
