#include <stdio.h>

#define N 100

// function to push an element onto the stack
void push(short *stack, short k, short *top) {
  // Check if stack is full
  if (*top == N) {
    printf("Stack overflow\n");
    return;
  }
  // Add element and inc stack pointer
  stack[(*top)++] = k;
}

// function to pop an element from the stack
short pop(short *stack, short *top) {
  // Check if stack is full
  if (*top == 0) {
    printf("Stack underflow\n");
    return -1;
  }

  // Take first element and dec stack pointer
  return stack[--(*top)];
}

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
    break;
  }
}

void calculatePostfix() {
  short stack[N], c, x, op1, op2, top = 0;

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
      push(stack, x, &top);
      continue;
    }

    // Unary minus on top element of stack
    if (c == '~') {
      if (top != 0) {
        op1 = pop(stack, &top);
        push(stack, -op1, &top);
      } else {
        printf("Error in input\n");
        return;
      }
    }

    // Binary operation on top two elements of stack
    if (c == '+' || c == '*' || c == '-') {
      if (top != 0) {
        op1 = pop(stack, &top);
        if (top != 0)
          op2 = pop(stack, &top);
        else {
          printf("Error in input\n");
          return;
        }
        push(stack, operation(op2, op1, c), &top);
      } else {
        printf("Invalid input\n");
        return;
      }
    }
  }

  // print result
  int result = pop(stack, &top);
  printf("Result: %d\n", result);
}
int main() {
  calculatePostfix();
  return 0;
}