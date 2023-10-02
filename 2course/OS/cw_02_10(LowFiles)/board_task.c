#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int fd, fd_tmp;
  long N, M;
  char *buf;
  if (argc != 3) {
    printf("Использование: %s <имя файла> <N>\n", argv[0]);
    exit(1);
  }
  fd = open(argv[1], O_RDWR);
  if (fd = -1) {
    printf("Ошибка при открытии файла\n");
    exit(1);
  }
  if (lseek(fd, 0, SEEK_END) >= 1024) {
    close(fd);
    printf("Файл не подходит под условие\n");
    exit(1);
  }
  lseek(fd, 0, SEEK_SET);
  N = strtol(argv[2], NULL, 10);
  fd_tmp = open("tmp", O_CREAT | O_RDWR, 0666);
  if (fd_tmp == -1) {
    printf("Ошибка при открытии файла\n");
    exit(1);
  }
  buf = (char *)malloc(N);
  while (M = read(fd, buf, N)) {
    write(fd_tmp, buf, M);
    write(fd_tmp, buf, M);
  }
  lseek(fd_tmp, 0, SEEK_SET);
  lseek(fd, 0, SEEK_SET);
  while (M = read(fd_tmp, buf, N)) {
    write(fd, buf, M);
  }
  close(fd);
  close(fd_tmp);
  unlink("tmp");

  return 0;
}