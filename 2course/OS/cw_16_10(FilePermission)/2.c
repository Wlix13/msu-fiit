/*
2) Напишите функцию, параметр int - права доступа к файлу в виде целого числа.
Вернуть указатель на строку, в которой в формате rwx (9 знаков) записаны
соответствующие права доступа к файлу. Вернуть значение NULL, если число не
входит в допустимый для задачи диапазон.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *modeToStr(int mode) {
  if (mode < 0 || mode > 0777)
    return NULL;

  const char pattern[] = "rwxrwxrwx";
  const int pattern_length = sizeof(pattern) - 1;

  char *result = malloc(pattern_length + 1); // or 9 + 1
  if (!result)
    return NULL;

  for (int i = 0; i < pattern_length; i++) {
    if (mode & (1 << (pattern_length - i - 1))) {
      result[i] = pattern[i];
    } else {
      result[i] = '-';
    }
  }
  result[pattern_length] = '\0';
  return result;
}

int main() {
  int test_num;
  printf("Enter permissions mode: ");
  scanf("%o", &test_num);

  char *int_result = modeToStr(test_num);
  if (int_result) {
    printf("Permissions: %s\n", int_result);
    free(int_result);
  } else {
    printf("Invalid permissions number.\n");
  }

  return 0;
}