#include <stdio.h>

void compress(char *s) {
  char *p = s, *q = s, prev = '\0';
  int count = 1;

  // Iterate through the string
  while (*p != '\0') {

    // If the current character is the same as the previous one
    if (*p == prev) {
      count++;

      // If the count is 10 or we are at the end of the string
      if (count == 10 || *(p + 1) == '\0') {
        *q++ = count + '0';
        *q++ = prev;
        count = 1;
      }
    } else {

      // If the count is greater than 1, we need to add the count to the string
      if (count > 1) {
        *q++ = count + '0';
        *q++ = prev;

        // If the count is 1, we need to add the previous character to the
        // string
      } else if (prev != '\0') {
        *q++ = prev;
      }

      // Set the previous character to the current character
      prev = *p;
      count = 1;
    }
    p++;
  }

  // Add the null terminator
  *q = '\0';
}

int main() {

  // Read string
  char s[50];
  scanf("%s", s);

  // Archive string
  compress(s);
  printf("%s\n", s);
  return 0;
}
