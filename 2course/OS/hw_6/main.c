/*
Работа с каталогом. Написать программу, которая для текущего каталога выполняет
следующие действия:

1) для каждого содержащегося в каталоге файла-символьной_ссылки вывести имя
файла, на который она ссылается.

2) если в каталоге есть подкаталоги, рекурсивно обойти все подкаталоги (для всех
уровней вложенности) и вывести на экран имена содержащихся в них исполняемых
файлов (только тех, для которых и пользователь, и группа (оба одновременно)
имеют право на исполнение файла).
Функцию смены каталога chdir не использовать.

Обратите внимание, что при обращении к функции stat/lstat нужно дополнить
полученное имя так, чтобы оно указывало на файл из соответствующего каталога.
*/

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

void process_directory(char *path) {
  DIR *dir;
  struct dirent *entry;
  struct stat statbuf;
  char full_path[1024];

  if ((dir = opendir(path)) == NULL) {
    fprintf(stderr, "Error opening dir %s\n", path);
    exit(1);
  }

  while ((entry = readdir(dir)) != NULL) {
    if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
      continue;

    sprintf(full_path, "%s/%s", path, entry->d_name);
    lstat(full_path, &statbuf);

    // Check if file is a symbolic link
    if (S_ISLNK(statbuf.st_mode)) {
      char target[1024];
      ssize_t len = readlink(full_path, target, sizeof(target) - 1);
      if (len != -1) {
        target[len] = '\0';
        printf("Symbolic link: %s -> %s\n", full_path, target);
      }
    }

    // Check if file is executable
    else if ((statbuf.st_mode & S_IXUSR) && (statbuf.st_mode & S_IXGRP)) {
      printf("Executable file: %s\n", full_path);
    }

    // Check if file is a directory then process it recursively
    else if (S_ISDIR(statbuf.st_mode)) {
      process_directory(full_path);
    }
  }

  closedir(dir);
}

int main() {
  process_directory(".");

  return 0;
}