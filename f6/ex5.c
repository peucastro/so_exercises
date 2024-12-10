#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static int flag = 1;
static void handler() { flag = 0; }
static void foo() {}

int main(int argc, char *argv[]) {
  printf("my PID is %d\n", getpid());
  if (signal(SIGINT, handler) == SIG_ERR) {
    fprintf(stderr, "Can't catch SIGINT: %s", strerror(errno));
    exit(EXIT_FAILURE);
  }
  if (signal(SIGTSTP, foo) == SIG_ERR) {
    fprintf(stderr, "Can't catch SIGTSTP: %s", strerror(errno));
    exit(EXIT_FAILURE);
  }
  if (signal(SIGHUP, foo) == SIG_ERR) {
    fprintf(stderr, "Can't catch SIGHUP: %s", strerror(errno));
    exit(EXIT_FAILURE);
  }
  if (signal(SIGQUIT, foo) == SIG_ERR) {
    fprintf(stderr, "Can't catch SIGQUIT: %s", strerror(errno));
    exit(EXIT_FAILURE);
  }
  /* enter potentially infinite loop ... */
  while (flag)
    pause();
  exit(EXIT_SUCCESS);
}
