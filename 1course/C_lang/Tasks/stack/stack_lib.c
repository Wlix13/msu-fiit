/*

Custom library to handle stack operations
1) Stack creation
2) Stack push
3) Stack pop

*/
#include <stdio.h>
#include "stack.h"

/*
Function to push an element onto the stack
Get:
    'int *stack' - pointer to stack
    'int k' - element to push
    'int *top' - pointer to stack pointer
Return:
    'void'
*/
void push(int *stack, int N, int k, int *top) {
  // Check if stack is full
  if (*top == N) {
    printf("Stack overflow\n");
    return;
  }
  // Add element and inc stack pointer
  stack[(*top)++] = k;
}


/*
Function to push an element onto the stack
Get:
    'int *stack' - pointer to stack
    'int *top' - pointer to stack pointer
Return:
    'int'
*/
int pop(int *stack, int N, int *top) {
  // Check if stack is full
  if (*top == 0) {
    printf("Stack underflow\n");
    return -1;
  }

  // Take first element and dec stack pointer
  return stack[--(*top)];
}

/*
Function to print stack
Get:
    'int *stack' - pointer to stack
    'int *top' - pointer to stack pointer
Return:
    'void'
*/
void printStack(int *stack, int *top) {
  // Check if stack is empty
  if (*top == 0) {
    printf("Stack is empty");
    return;
  }

  // Print stack
  for (int i = 0; i < *top; i++) {
    printf("%d ", stack[i]);
  };
  printf("\n");
}