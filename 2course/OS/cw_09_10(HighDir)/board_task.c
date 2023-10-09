/*
В командной строке задано имя католога(если не задано, то текущий). Для
заданного католога:
1) Вывести мена всех файлов, начинающихся с точки и его размер
2) Если файл регулярный, то вывести время последней модификации(Если есть доступ
к файлу)
*/

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  DIR *dir;
  struct dirent *entry;
  struct stat *statbuff;
  char *dir_name;

  if (argc == 1) {
    dir_name = ".";
  } else {
    dir_name = argv[1];
  }

  if ((dir = opendir(dir_name)) == NULL) {
    fprintf(stderr, "Can't open %s\n", dir_name);
    exit(1);
  }

  while ((entry = readdir(dir)) != NULL) {
    if (entry->d_name[0] == '.') {
      sprintf(dir_name, "%s/%s", dir_name, entry->d_name);
      if (lstat(dir_name, statbuff) == -1) {
        fprintf(stderr, "Can't stat %s\n", dir_name);
        continue;
      }
      printf("%s - %lld\n", dir_name, statbuff->st_size);

      if ((S_IFMT & statbuff->st_mode) == S_IFREG &&
          (statbuff->st_mode & S_IRWXU) == S_IXUSR) {
        printf("Last modified: %s", ctime(&statbuff->st_mtime));
      }
    }
  }

  closedir(dir);
  return 0;
}