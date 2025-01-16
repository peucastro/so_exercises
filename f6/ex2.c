#include <ctype.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <unistd.h>

#define BUFFER_SIZE 4096

void to_uppercase(char *str) {
  for (int i = 0; str[i]; i++) {
    str[i] = toupper(str[i]);
  }
}

int main(int argc, char *argv[]) {
  char buffer[BUFFER_SIZE];
  int sockets[2], retv;
  retv = socketpair(AF_UNIX, SOCK_STREAM, 0, sockets);
  if (retv == -1) {
    perror("socketpair");
    exit(EXIT_FAILURE);
  }
  retv = fork();
  if (retv == -1) {
    perror("fork");
    exit(EXIT_FAILURE);
  }
  if (retv > 0) { /* parent */
    int file = open(argv[1], O_RDONLY);
    if (file == -1) {
      perror("error: cannot open file");
      exit(EXIT_FAILURE);
    }
    close(sockets[0]);
    int nbytes = read(file, buffer, BUFFER_SIZE);
    while (nbytes > 0) {
      write(sockets[1], buffer, nbytes);
      nbytes = read(sockets[1], buffer, nbytes);
      write(STDOUT_FILENO, buffer, nbytes);
      nbytes = read(file, buffer, BUFFER_SIZE);
    }
    close(file);
    close(sockets[1]);
    retv = wait(NULL);
    if (retv == -1) {
      perror("wait");
      exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
  } else { /* child */
    close(sockets[1]);
    int nbytes = read(sockets[0], buffer, sizeof(buffer));
    while (nbytes > 0) {
      to_uppercase(buffer);
      write(sockets[0], buffer, nbytes);
      nbytes = read(sockets[0], buffer, sizeof(buffer));
    }
    close(sockets[0]);
    exit(EXIT_SUCCESS);
  }
}
