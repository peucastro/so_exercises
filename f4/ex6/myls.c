#include <dirent.h>
#include <grp.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

void print_file_info(const char *path, const char *filename) {
  struct stat fileStat;
  char fullPath[PATH_MAX];

  snprintf(fullPath, sizeof(fullPath), "%s/%s", path, filename);
  if (stat(fullPath, &fileStat) == -1) {
    return;
  }

  // File type
  printf((S_ISDIR(fileStat.st_mode)) ? "d" : "-");
  printf((fileStat.st_mode & S_IRUSR) ? "r" : "-");
  printf((fileStat.st_mode & S_IWUSR) ? "w" : "-");
  printf((fileStat.st_mode & S_IXUSR) ? "x" : "-");
  printf((fileStat.st_mode & S_IRGRP) ? "r" : "-");
  printf((fileStat.st_mode & S_IWGRP) ? "w" : "-");
  printf((fileStat.st_mode & S_IXGRP) ? "x" : "-");
  printf((fileStat.st_mode & S_IROTH) ? "r" : "-");
  printf((fileStat.st_mode & S_IWOTH) ? "w" : "-");
  printf((fileStat.st_mode & S_IXOTH) ? "x" : "-");

  // Number of links
  printf(" %ld", fileStat.st_nlink);

  // Owner and group names
  struct passwd *pw = getpwuid(fileStat.st_uid);
  struct group *gr = getgrgid(fileStat.st_gid);
  printf(" %s %s", pw ? pw->pw_name : "UNKNOWN", gr ? gr->gr_name : "UNKNOWN");

  // File size
  printf(" %5ld", fileStat.st_size);

  // Modification time
  char timeStr[20];
  strftime(timeStr, sizeof(timeStr), "%b %d %H:%M",
           localtime(&fileStat.st_mtime));
  printf(" %s", timeStr);

  // File name
  printf(" %s\n", filename);
}

void list_directory(const char *path) {
  DIR *dir = opendir(path);
  if (dir == NULL) {
    exit(EXIT_FAILURE);
  }

  struct dirent *entry;
  while ((entry = readdir(dir)) != NULL) {
    // Skip "." and ".."
    if (entry->d_name[0] == '.' &&
        (entry->d_name[1] == '\0' ||
         (entry->d_name[1] == '.' && entry->d_name[2] == '\0'))) {
      continue;
    }
    print_file_info(path, entry->d_name);
  }

  closedir(dir);
}

int main(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <dirname|filename>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  struct stat pathStat;
  if (stat(argv[1], &pathStat) == -1) {
    exit(EXIT_FAILURE);
  }

  if (S_ISDIR(pathStat.st_mode)) {
    list_directory(argv[1]);
  } else {
    print_file_info(".", argv[1]);
  }

  exit(EXIT_SUCCESS);
}
