#include <stdio.h>
#include "stack.h"

#define N 100

// Function to get priority of operator
int priory(int c) {
  switch (c) {
  case '+':
  case '-':
    return 1;
  case '*':
    return 2;
  case '~':
    return 3;
  default:
    return 0;
  }
}

// Function to convert infix to postfix notation
void infix_to_postfix() {
  int stack[N], op, top = 0, c = 0, last = '(';
  push(stack, N, last, &top);

  // Loop through input characters
  while (c != '\n' && c != EOF) {
    while ((c = getchar()) == ' ') {
    }

    // If c is a digit, print it
    if (c >= '0' && c <= '9') {
      while (c >= '0' && c <= '9') {
        putchar(c);
        last = c;
        c = getchar();
      }
      putchar(' ');
    }

    // Skip newline or whitespace
    if (c == '\n' || c == ' ') {
      continue;
    }

    // Check if input is valid
    if (priory(c) == 0 && c != '(' && c != ')' && (c < '0' || c > '9')) {
      printf("Invalid input\n");
      return;
    }

    // Handle negative sign
    if ((priory(last) > 0 || last == '(' || last == ')') && c == '-') {
      c = '~';
      push(stack, N, c, &top);
    }

    // Handle open parenthesis
    if (c == '(') {
      push(stack, N, c, &top);
    }

    // Handle close parenthesis
    if (c == ')') {
      while ((op = pop(stack, N, &top)) != '(') {
        putchar(op);
        putchar(' ');
      }
    }

    // Handle operator
    if (priory(c) != 0 && c != '~') {
      while ((op = pop(stack, N, &top)) != '(' && priory(op) >= priory(c)) {
        putchar(op);
        putchar(' ');
      }
      push(stack, N, op, &top);
      push(stack, N, c, &top);
    }
    last = c;
  }

  // Print the remaining operators on the stack
  while ((op = pop(stack, N, &top)) != '(') {
    putchar(op);
    putchar(' ');
  }
  putchar('\n');
}

int main() {
  infix_to_postfix();
  return 0;
}