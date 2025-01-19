#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

char *change_filename_extension(const char *filename) {
  const char *dot = strrchr(filename, '.'); // Find the last '.' in the filename
  size_t base_length = dot ? (size_t)(dot - filename) : strlen(filename);

  // Allocate memory for the new filename
  char *new_filename = malloc(base_length + 6); // 5 for ".epub" + 1 for '\0'
  if (!new_filename) {
    fprintf(stderr, "Memory allocation failed\n");
    return NULL;
  }

  // Copy the base filename and append ".epub"
  strncpy(new_filename, filename, base_length);
  strcpy(new_filename + base_length, ".epub");

  return new_filename;
}

char *remove_filename_extension(const char *filename) {
  const char *dot = strrchr(filename, '.'); // Find the last '.' in the filename
  size_t base_length = dot ? (size_t)(dot - filename) : strlen(filename);

  // Allocate memory for the new filename (excluding the extension)
  char *new_filename = malloc(base_length + 1); // +1 for '\0'
  if (!new_filename) {
    fprintf(stderr, "Memory allocation failed\n");
    return NULL;
  }

  // Copy the base filename without the extension
  strncpy(new_filename, filename, base_length);
  new_filename[base_length] = '\0'; // Null-terminate the string

  return new_filename;
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("correct usage:\n    $ text2epub book1.txt book2.txt ...\n");
    perror("wrong arguments");
    exit(EXIT_FAILURE);
  }

  char *title_parameter;
  for (int i = 1; i < argc; i++) {
    pid_t pid = fork();
    if (pid == -1) { // error
      perror("fork");
      exit(EXIT_FAILURE);
    } else if (pid == 0) { // child
      printf("[pid:%d] converting %s\n", getpid(), argv[i]);
      title_parameter =
          (char *)malloc((strlen(argv[i] - 4) + 8) * sizeof(char));
      strcpy(title_parameter, "title=\"");
      strcat(title_parameter, remove_filename_extension(argv[i]));
      strcat(title_parameter, "\"");
      int retv = execlp("/usr/bin/pandoc", "pandoc", argv[i], "-o",
                        change_filename_extension(argv[i]), "--metadata",
                        title_parameter, NULL);
      free(title_parameter);
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

  for (int i = 1; i < argc; i++)
    wait(NULL);

  char *command[argc + 2];
  command[0] = "zip";
  command[1] = "ebooks.zip";
  int j = 2;
  for (int i = 1; i < argc; i++) {
    command[j++] = change_filename_extension(argv[i]);
  }
  command[j] = NULL;

  int retv = execvp("/usr/bin/zip", command);
  if (retv == -1) {
    perror("execvp");
    exit(EXIT_FAILURE);
  }

  exit(EXIT_SUCCESS);
}
