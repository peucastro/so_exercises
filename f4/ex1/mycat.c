#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("usage: ./mycat filename1 filename2 ...\n");
    exit(EXIT_FAILURE);
  }

  for (int i = 1; i < argc; i++) {
    int fd = open(argv[i], O_RDONLY);
    if (fd == -1) {
      printf("error: cannot open %s\n", argv[1]);
      exit(EXIT_FAILURE);
    }

    char buffer[BUFFER_SIZE];
    int nbytes = read(fd, buffer, BUFFER_SIZE);
    while (nbytes > 0) {
      write(STDOUT_FILENO, buffer, nbytes);
      nbytes = read(fd, buffer, BUFFER_SIZE);
    }

    close(fd);
  }

  exit(EXIT_SUCCESS);
}
