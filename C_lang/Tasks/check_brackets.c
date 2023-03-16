#include <stdio.h>
#include <string.h>

#define N 10

char stack[N];
int top = -1;

void push(char *stack, int *top, char bracket) {
  if (*top == N - 1) {
    printf("Stack overflow\n");
    return;
  }
  stack[(*top)++] = bracket;
}

char pop(char *stack, int *top) {
  if (*top == -1) {
    printf("Stack underflow\n");
    return 0;
  }
  return stack[--(*top)];
}

int isMatchingPair(char left, char right) {
  if (left == '(' && right == ')')
    return 1;
  else if (left == '{' && right == '}')
    return 1;
  else if (left == '[' && right == ']')
    return 1;
  else
    return 0;
}

int isBalanced(char *stack, int *top) {
  for (int i = 0; i < *top; i++) {
    if (stack[i] == '(' || stack[i] == '{' || stack[i] == '[')
      push(stack, top, stack[i]);
    else if (stack[i] == ')' || stack[i] == '}' || stack[i] == ']') {
      if (*top == -1 || !isMatchingPair(pop(stack, top), stack[i]))
        return 0;
    }
  }
  if (*top == -1)
    return 1;
  else
    return 0;
}

int main() {
  // Строка из последовательности
  char expression[N];
  printf("Enter an expression: ");
  scanf("%s", expression);

  // Проверка на балансировку скобок
  printf("%d", isBalanced(expression, &top));
  if (isBalanced(expression, &top))
    printf("Expression is balanced\n");
  else
    printf("Expression is not balanced\n");
  return 0;
}