// $ (cmd1 < file1 && cmd2) | cmd3 >> file2
// ./main cmd1 file1 cmd2 cmd3 file2 (./main cat board.c wc cat board.c)

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int arg, char *argv[]) {
  int fd[2];
  int status;
  pid_t pid_1, pid_2;

  pipe(fd);

  if ((fork()) == 0) {
    if ((pid_1 = fork()) == 0) {
      // cmd1 input from file
      int fd1 = open(argv[2], O_RDONLY);
      dup2(fd1, 0);
      close(fd1);

      // cmd1 output to pipe
      close(fd[0]);
      dup2(fd[1], 1);
      close(fd[1]);

      execlp(argv[1], argv[1], NULL);
      perror("execlp");
      exit(1);
    }
    waitpid(pid_1, &status, 0);

    // check cmd1 result
    if (!WIFEXITED(status) || WEXITSTATUS(status) != 0)
      exit(1);

    // cmd2 output to pipe
    if ((fork()) == 0) {
      close(fd[0]);
      dup2(fd[1], 1);
      close(fd[1]);

      execlp(argv[3], argv[3], NULL);
      perror("execlp");
      exit(1);
    }

    exit(0);
  }
  if ((fork()) == 0) {
    // cmd3 input from pipe
    close(fd[1]);
    dup2(fd[0], 0);
    close(fd[0]);

    // cmd3 output to file
    int fd2 = open(argv[5], O_WRONLY | O_CREAT | O_APPEND, 0666);
    dup2(fd2, 1);
    close(fd2);

    execlp(argv[4], argv[4], NULL);
    perror("execlp");
    exit(1);
  }

  close(fd[0]);
  close(fd[1]);

  wait(NULL);
  wait(NULL);

  return 0;
}