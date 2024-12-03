#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

void get_args(char *command, char **args) {
  char *p;
  int i = 0;
  p = strtok(command, " ");
  while (p != NULL) {
    args[i++] = strdup(p);
    p = strtok(NULL, " ");
  }
  args[i] = NULL;
}

int main(int argc, char *argv[]) {
  for (;;) {
    /* give prompt, read command, and null terminate it */
    fprintf(stdout, "$ ");
    char buf[1024];
    char *command = fgets(buf, sizeof(buf), stdin);
    command[strlen(buf) - 1] = '\0';
    if (command == NULL || strcmp(command, "exit") == 0)
      break;

    /* call fork and check return value */
    pid_t pid = fork();
    if (pid == -1) {
      perror("fork");
      exit(EXIT_FAILURE);
    }

    if (pid == 0) {
      char *args[64];
      get_args(command, args);
      int retv = execvp(args[0], args);
      if (retv == -1) {
        perror("execvp");
        exit(EXIT_FAILURE);
      }
    }

    /* Parent process waits for the child to finish */
    int retv = waitpid(pid, NULL, 0);
    if (retv == -1) {
      perror("waitpid");
      exit(EXIT_FAILURE);
    }
  }

  exit(EXIT_SUCCESS);
}
