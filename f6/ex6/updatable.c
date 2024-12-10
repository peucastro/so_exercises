#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/errno.h>
#include <sys/time.h>
#include <unistd.h>

static int param; /* program parameter */

void read_parameter() {
  FILE *fp = fopen(".config", "r");
  fscanf(fp, "param: %d\n", &param);
  fclose(fp);
}

void write_parameter() { printf("param value is: %d\n", param); }

void handler(int signum) {
  read_parameter();
  write_parameter();
}

int main(int argc, char *argv[]) {
  if (signal(SIGHUP, handler) == SIG_ERR) {
    fprintf(stderr, "Can't catch SIGHUP: %s", strerror(errno));
    exit(EXIT_FAILURE);
  }

  printf("my PID is %d\n", getpid());
  read_parameter();
  printf("waiting...\n");
  for (;;)
    pause();
}
