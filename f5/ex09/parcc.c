#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  if (argc < 4 || strcmp(argv[1], "-o") != 0) {
    printf("correct usage:\n    $ parcc -o prog prog1.c prog2.c ...\n");
    perror("wrong arguments");
    exit(EXIT_FAILURE);
  }

  for (int i = 3; i < argc; i++) {
    pid_t pid = fork();
    if (pid == -1) { // error
      perror("fork");
      exit(EXIT_FAILURE);
    } else if (pid == 0) { // child
      printf("[pid:%d] compiling %s\n", getpid(), argv[i]);
      int retv = execlp("/usr/bin/gcc", "gcc", "-Wall", "-c", argv[i], NULL);
      if (retv == -1) {
        perror("execlp");
        exit(EXIT_FAILURE);
      }
      exit(EXIT_SUCCESS);
    } else { // parent
      int retv = waitpid(pid, NULL, 0);
      if (retv == -1) {
        perror("waitpid");
        exit(EXIT_FAILURE);
      }
    }
  }

  for (int i = 3; i < argc; i++)
    wait(NULL);

  char buf[1024];
  char *file;
  char *command[argc + 4];
  command[0] = "gcc";
  command[1] = "-Wall";
  int j = 2;
  for (int i = 3; i < argc; i++) {
    file = (char *)malloc(strlen(argv[i]) * sizeof(char));
    strcpy(buf, argv[i]);

    if (buf[strlen(buf) - 1] == 'c') {
      buf[strlen(buf) - 1] = 'o';
      buf[strlen(buf)] = '\0';
      strcpy(file, buf);
      command[j++] = file;
    }
  }
  command[j++] = "-o";
  command[j++] = argv[2];
  command[j++] = "-lm";
  command[j] = NULL;

  int retv = execvp("/usr/bin/gcc", command);
  if (retv == -1) {
    perror("execvp");
    exit(EXIT_FAILURE);
  }

  exit(EXIT_SUCCESS);
}
