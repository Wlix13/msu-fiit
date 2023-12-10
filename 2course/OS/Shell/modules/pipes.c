#include "pipes.h"
#include "utils.h"

/*
 * Function to make output of process go to file descriptor
 * @param fd - pipe to redirect
 * @param d - file descriptor to redirect to
 */
pid_t pipeToFD(int fd[2], int d) {
  pid_t pid;
  if ((pid = fork()) == 0) {
    if (DEBUG)
      printf("DEBUG: Pipe created: %d -> %d\n", fd[READ_END], d);

    closeIrrelevantFDs((int[]){fd[READ_END], d, -1});

    int len;
    char buf[CHUNK];

    while ((len = read(fd[READ_END], &buf, sizeof(buf))))
      write(d, &buf, len);

    if (DEBUG)
      printf("DEBUG: Pipe closed: %d -> %d\n", fd[READ_END], d);

    closeIrrelevantFDs((int[]){-1});
    exit(EXIT_SUCCESS);
  }

  close(fd[READ_END]);
  close(fd[WRITE_END]);

  return pid;
}

/*
 * Function to make output of process go to file
 * @param fd - pipe to redirect
 * @param file - file to redirect to
 * @param append - flag to determine if file should be appended
 */
pid_t pipeToFile(int fd[2], char *file, int append) {
  pid_t pid;
  if ((pid = fork()) == 0) {
    if (DEBUG)
      printf("DEBUG: Pipe created: %d -> FILE(%s)\n", fd[READ_END], file);

    closeIrrelevantFDs((int[]){fd[READ_END], -1});

    int f =
        open(file, O_WRONLY | O_CREAT | (!append ? O_TRUNC : O_APPEND), 0666);

    if (f == -1) {
      close(fd[READ_END]);
      if (DEBUG)
        printf("DEBUG: Pipe crashed: %d -> FILE(%s)\n", fd[READ_END], file);
      exit(EXIT_FAILURE);
    }

    int len;
    char buf[CHUNK];

    while ((len = read(fd[READ_END], &buf, sizeof(buf))))
      write(f, &buf, len);

    close(f);
    close(fd[READ_END]);
    if (DEBUG)
      printf("DEBUG: Pipe exited: %d -> FILE(%s)\n", fd[READ_END], file);
    exit(EXIT_SUCCESS);
  }

  close(fd[READ_END]);
  close(fd[WRITE_END]);

  return pid;
}

/*
 * Function to make input of process go from file
 * @param fd - pipe to redirect
 * @param file - file to redirect from
 */
pid_t pipeFromFile(int fd[2], char *file) {
  pid_t pid;
  if ((pid = fork()) == 0) {
    if (DEBUG)
      printf("DEBUG: Pipe created: FILE(%s) -> %d\n", file, fd[WRITE_END]);

    closeIrrelevantFDs(
        (int[]){STDOUT_FILENO, STDERR_FILENO, fd[WRITE_END], -1});

    int f = open(file, O_RDONLY);
    if (f == -1) {
      exit(EXIT_FAILURE);
    }

    int len;
    char buf[CHUNK];

    while ((len = read(f, &buf, sizeof(buf))))
      write(fd[WRITE_END], &buf, len);

    if (DEBUG)
      printf("DEBUG: Pipe exited: FILE(%s) -> %d\n", file, fd[WRITE_END]);

    closeIrrelevantFDs((int[]){-1});
    exit(EXIT_SUCCESS);
  }

  return pid;
}

/*
 * Function to make input of process go from pipe and output go to pipe
 * @param fd1 - pipe to redirect from
 * @param fd2 - pipe to redirect to
 */
pid_t pipeFromTo(int fd1[2], int fd2[2]) {
  pid_t pid;
  if ((pid = fork()) == 0) {
    if (DEBUG)
      printf("DEBUG: Pipe created: %d -> %d\n", fd1[0], fd2[1]);

    closeIrrelevantFDs((int[]){STDOUT_FILENO, fd1[0], fd2[1], -1});

    int len;
    char buf[CHUNK];

    while ((len = read(fd1[0], &buf, sizeof(buf))))
      write(fd2[1], &buf, len);

    if (DEBUG)
      printf("DEBUG: Pipe exited: %d -> %d\n", fd1[0], fd2[1]);

    exit(EXIT_SUCCESS);
  }

  return pid;
}