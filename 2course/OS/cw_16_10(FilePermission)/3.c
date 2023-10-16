/*
3) Для всех файлов из текущего каталога вывести на экран имя файла, номер его
индексного дескриптора, тип файла в виде текстовой строки и права доступа в
формате строки rwx.
*/

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#ifndef S_IFLNK
#define S_IFLNK 0120000
#endif

const char *modeToFiletype(mode_t mode) {
  switch (mode & S_IFMT) {
  case S_IFBLK:
    return "Block device";
  case S_IFCHR:
    return "Character device";
  case S_IFDIR:
    return "Directory";
  case S_IFLNK:
    return "Symlink";
  case S_IFREG:
    return "Regular file";
  default:
    return "Unknown";
  }
}

char *modeToPermission(mode_t mode) {
  char *permissions = (char *)malloc(10); // 9 mode bits + '\0'
  if (!permissions) {
    return NULL;
  }

  const char chars[] = "rwxrwxrwx";

  unsigned int mask = 1 << 8;
  for (int i = 0; i < 9; i++) {
    permissions[i] = (mode & mask) ? chars[i] : '-';
    mask >>= 1;
  }
  permissions[9] = '\0';
  return permissions;
}

void printAll() {
  DIR *dir;
  struct dirent *entry;
  struct stat file_stat;

  dir = opendir(".");
  if (!dir) {
    fprintf(stderr, "Error opening dir\n");
    return;
  }

  while ((entry = readdir(dir)) != NULL) {
    if (lstat(entry->d_name, &file_stat) == -1) {
      fprintf(stderr, "Error getting file attributes\n");
      continue;
    }
    char *permissions = modeToPermission(file_stat.st_mode);
    printf("Filename: %s\n", entry->d_name);
    printf("Inode: %ld\n", (long)entry->d_ino);
    printf("Type: %s\n", modeToFiletype(file_stat.st_mode));
    printf("Permissions: %s\n\n", permissions);
    free(permissions);
  }

  closedir(dir);
  return;
}

int main() {
  printAll();

  return 0;
}