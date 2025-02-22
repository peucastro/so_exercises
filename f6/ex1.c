#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define BUFFER_SIZE 4096

int main(int argc, char *argv[]) {
  int fd[2];
  pid_t pid;
  if (pipe(fd) == -1) {
    perror("pipe");
    exit(EXIT_FAILURE);
  }
  if ((pid = fork()) == -1) {
    perror("fork");
    exit(EXIT_FAILURE);
  }
  if (pid > 0) { /* parent */
    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
      perror("error: cannot open file");
      exit(EXIT_FAILURE);
    }
    close(fd[0]);
    char buffer[BUFFER_SIZE];
    size_t nbytes;
    while ((nbytes = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
      write(fd[1], buffer, nbytes);
    }
    fclose(file);
    close(fd[1]);
    if (wait(NULL) == -1) {
      perror("wait");
      exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
  } else { /* child */
    char buffer[BUFFER_SIZE];
    close(fd[1]);
    int nbytes = read(fd[0], buffer, BUFFER_SIZE);
    write(STDOUT_FILENO, buffer, nbytes);
    close(fd[0]);
    exit(EXIT_SUCCESS);
  }
}
