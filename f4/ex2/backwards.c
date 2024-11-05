#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("usage: ./backwards filename\n");
    exit(EXIT_FAILURE);
  }

  int fd = open(argv[1], O_RDONLY);
  if (fd == -1) {
    printf("error: cannot open %s\n", argv[1]);
    exit(EXIT_FAILURE);
  }

  char buffer[1];
  int nbytes = lseek(fd, 0, SEEK_END);
  for (int i = 1; i <= nbytes; i++) {
    lseek(fd, -i, SEEK_END);
    read(fd, buffer, 1);
    write(STDOUT_FILENO, buffer, 1);
  }
  write(STDOUT_FILENO, "\n", 1);

  close(fd);
  exit(EXIT_SUCCESS);
}
