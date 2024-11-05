#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>

int main(int argc, char *argv[]) {
  struct stat info;
  if (argc < 2) {
    fprintf(stderr, "usage: %s file1 file2 ...\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  for (int i = 1; i < argc; i++) {
    int retv = stat(argv[i], &info);
    if (retv == -1) {
      fprintf(stderr, "%s: Can't stat %s\n", argv[0], argv[i]);
      exit(EXIT_FAILURE);
    }

    char *modification_time = ctime(&info.st_mtime);
    modification_time[strlen(modification_time) - 1] = '\0';

    printf("%s size: %d bytes, disk_blocks: %d, date of last change: %s, owner "
           "UID: %d\n",
           argv[i], (int)info.st_size, (int)info.st_blocks, modification_time,
           (int)info.st_uid);
  }

  exit(EXIT_SUCCESS);
}
