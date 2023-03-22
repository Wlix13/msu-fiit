/* Не используя библиотеку string.h и не используя операцию индексирования []
реализовать функции

mystrcat (аналогично strcat - добавление второй строки в конец первой),

mystrchr (аналогично strchr - поиск первого вхождения заданного символа в
строке),

mystrrchr (аналогично strrchr - поиск последнего вхождения заданного символа в
строке). */

#include <stdio.h>

// Function strcat() appends the string pointed to by src to the end of the
char *mystrcat(char *dest, const char *src) {

  // Find the end of the destination string.
  char *p = dest;
  while (*p) {
    p++;
  }

  // Append characters from the source string to the destination string.
  while (*(++src)) {
    *p = *src;
    p++;
    src++;
  }

  // Add the terminator to the destination string.
  *p = '\0';
  return dest;
}

//  Function strchr() returns a pointer to the first occurrence of the character
//  c in the string str.
char *mystrchr(const char *str, int c) {
  // Find the first occurrence of c in str.
  while (*str) {
    if (*str == c) {
      return (char *)str;
    }
    str++;
  }

  // If c is '\0', return a pointer to the null character at the end of str.
  if (c == '\0') {
    return (char *)str;
  }

  // If c is not found, return a null pointer.
  return NULL;
}

// Function strrchr() returns a pointer to the last occurrence of the character
char *mystrrchr(const char *str, int c) {

  // Find the last occurrence of c in str.
  char *last_occurrence = NULL;
  while (*str) {
    if (*str == c) {
      last_occurrence = (char *)str;
    }
    str++;
  }

  // If c is '\0', return a pointer to the null character at the end of str.
  if (last_occurrence) {
    return last_occurrence;
  }
  if (c == '\0') {
    return (char *)str;
  }

  return NULL;
}

int main() {
  char str1[50] = "Hello, ";
  char str2[50] = "world!";
  char c1 = 'o';
  char c2 = 'l';

  mystrcat(str1, str2);
  printf("After mystrcat: %s\n", str1);

  char *p1 = mystrchr(str1, c1);
  printf("First occurrence of '%c': %s\n", c1, p1);

  char *p2 = mystrrchr(str1, c2);
  printf("Last occurrence of '%c': %s\n", c2, p2);

  return 0;
}