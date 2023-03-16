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
  short stack[N], op, top = 0, c = 0, last = '(';
  push(stack, last, &top);

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
      push(stack, c, &top);
    }

    // Handle open parenthesis
    if (c == '(') {
      push(stack, c, &top);
    }

    // Handle close parenthesis
    if (c == ')') {
      while ((op = pop(stack, &top)) != '(') {
        putchar(op);
        putchar(' ');
      }
    }

    // Handle operator
    if (priory(c) != 0 && c != '~') {
      while ((op = pop(stack, &top)) != '(' && priory(op) >= priory(c)) {
        putchar(op);
        putchar(' ');
      }
      push(stack, op, &top);
      push(stack, c, &top);
    }
    last = c;
  }

  // Print the remaining operators on the stack
  while ((op = pop(stack, &top)) != '(') {
    putchar(op);
    putchar(' ');
  }
  putchar('\n');
}

int main() {
  infix_to_postfix();
  return 0;
}