#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

#define MAX_LEN 1024

int main(int arg, char *argv[]) {
  int fd1[2], fd2[2];
  int pos = 0;
  char buf[MAX_LEN];
  pid_t pid;
  pipe(fd1);
  pipe(fd2);

  if ((fork()) == 0) {
    close(fd1[1]);
    while (read(fd1[0], buf, MAX_LEN) > 0) {
      // Somet func to process string
      // reverse_string(buf);
      write(fd2[1], buf, MAX_LEN);
    }
    close(fd1[0]);
    close(fd2[0]);
    close(fd2[1]);
    exit(0);
  }

  FILE *file = fopen(argv[1], "r+");
  pos = ftell(file);
  close(fd1[0]);
  close(fd2[1]);
  while (fgets(buf, MAX_LEN, file) != NULL) {
    write(fd1[1], buf, MAX_LEN);
    read(fd2[0], buf, MAX_LEN);
    fseek(file, pos, SEEK_SET);
    fputs(buf, file);
    pos = ftell(file);
  }
  close(fd1[1]);
  close(fd2[0]);

  wait(NULL);

  return 0;
}