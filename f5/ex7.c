#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

void write_history(const char *command) {
  // Don't write "myhistory" commands to history
  if (strncmp(command, "myhistory", 9) != 0) {
    FILE *history_file = fopen("history.txt", "a");
    if (history_file == NULL) {
      perror("failed to open history file");
      exit(EXIT_FAILURE);
    }
    fprintf(history_file, "%s\n", command);
    fflush(history_file);
    fclose(history_file);
  }
}

void show_history(int n) {
  FILE *history_file = fopen("history.txt", "r");
  if (history_file == NULL) {
    perror("failed to open history file");
    exit(EXIT_FAILURE);
  }

  // Count total lines in file
  int total_lines = 0;
  char ch;
  while ((ch = fgetc(history_file)) != EOF) {
    if (ch == '\n')
      total_lines++;
  }

  // Reset file pointer to beginning
  rewind(history_file);

  // Calculate how many lines to skip
  int lines_to_skip = total_lines > n ? total_lines - n : 0;

  // Skip lines if necessary
  for (int i = 0; i < lines_to_skip; i++) {
    while ((ch = fgetc(history_file)) != EOF && ch != '\n')
      ;
  }

  // Read and display the last n lines
  char line[1024];
  while (fgets(line, sizeof(line), history_file) != NULL) {
    printf("%s", line);
  }

  fclose(history_file);
}

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
    if (command == NULL)
      break;

    command[strlen(buf) - 1] = '\0';

    if (strcmp(command, "exit") == 0)
      break;

    write_history(command);

    /* Parse command into arguments */
    char *args[64];
    get_args(command, args);

    /* Handle myhistory command directly without forking */
    if (strcmp(args[0], "myhistory") == 0) {
      if (args[1] == NULL) {
        fprintf(stderr, "myhistory: missing argument\n");
        continue;
      }
      int n = atoi(args[1]);
      if (n <= 0) {
        fprintf(stderr, "myhistory: invalid number\n");
        continue;
      }
      show_history(n);
      continue;
    }

    /* For other commands, fork and execute */
    pid_t pid = fork();
    if (pid == -1) {
      perror("fork");
      exit(EXIT_FAILURE);
    }

    if (pid == 0) {
      int retv = execvp(args[0], args);
      if (retv == -1) {
        perror("exec");
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
