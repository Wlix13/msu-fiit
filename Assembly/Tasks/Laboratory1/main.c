#include "lib.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 101

int main() {
  char str[N];

  printf("Enter a string (max 100 characters): ");
  scanf("%s", str);

  int len = strlen(str);

  // Check if first & last characters are letters
  if (isalpha(str[0]) && isalpha(str[len - 1])) {
    printf("Rule 1 usage\n");
    printf("Derived string:\n%s\n", rule1(str));
    return 0;
  } else {
    // Any other case
    printf("Rule 2 usage\n");
    printf("Derived string:\n%s\n", rule2(str));
    return 0;
  }
}
