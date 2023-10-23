// ls -lR | wc

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  int fd[2];
  pipe(fd);
  pid_t p1, p2;

  if ((p1 = fork()) == 0) {
    close(fd[0]);
    dup2(fd[1], 1);
    close(fd[1]);
    execlp("ls", "ls", "-lR", NULL);
    perror("ls");
    exit(1);
  } else if ((p2 = fork()) == 0) {
    close(fd[1]);
    dup2(fd[0], 0);
    close(fd[0]);
    execlp("wc", "wc", NULL);
    perror("wc");
    exit(1);
  }

  close(fd[0]);
  close(fd[1]);

  wait(NULL);
  wait(NULL);

  return 0;
}