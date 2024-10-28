#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("Correct usage: ./mycat filename1 filename2 ...\n");
    exit(EXIT_FAILURE);
  }

  for (int i = 1; i < argc; i++) {
    FILE *file = fopen(argv[i], "r");
    if (file == NULL) {
      printf("error: could not open %s\n", argv[1]);
      exit(EXIT_FAILURE);
    }

    char buffer[BUFFER_SIZE];
    int nchars = fread(buffer, sizeof(char), BUFFER_SIZE, file);
    while (nchars > 0) {
      fwrite(buffer, sizeof(char), nchars, stdout);
      nchars = fread(buffer, sizeof(char), BUFFER_SIZE, file);
    }

    fclose(file);
  }

  exit(EXIT_SUCCESS);
}
