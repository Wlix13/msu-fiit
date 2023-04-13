#include <stdio.h>
#include "stack.h"

#define N 100


// function to perform an arithmetic operation
short operation(short a, short b, short c) {
  switch (c) {
  case '+':
    return a + b;
  case '*':
    return a * b;
  case '-':
    return a - b;
  default:
    printf("Invalid operator: %c\n", c);
    return 0;
  }
}

void calculatePostfix() {
  // create stack
  int stack[N];
  int c, x, op1, op2, top = 0;

  // read input from stdio
  while ((c = getchar()) != '\n' && c != EOF) {
    if (c == ' ')
      continue;

    // read number up to whitespace and push onto stack
    if (c >= '0' && c <= '9') {
      x = 0;
      while (c != ' ') {
        x = x * 10 + (c - '0');
        c = getchar();
      }
      push(stack, N, x, &top);
      continue;
    }

    // Unary minus on top element of stack
    if (c == '~') {
      if (top != 0) {
        op1 = pop(stack, N, &top);
        push(stack, N, -op1, &top);
      } else {
        printf("Error in input\n");
        return;
      }
    }

    // Binary operation on top two elements of stack
    if (c == '+' || c == '*' || c == '-') {
      if (top != 0) {
        op1 = pop(stack, N, &top);
        if (top != 0)
          op2 = pop(stack, N, &top);
        else {
          printf("Error in input\n");
          return;
        }
        push(stack, N, operation(op2, op1, c), &top);
      } else {
        printf("Invalid input\n");
        return;
      }
    }
  }

  // print result
  int result = pop(stack, N, &top);
  printf("Result: %d\n", result);
}
int main() {
  calculatePostfix();
  return 0;
}