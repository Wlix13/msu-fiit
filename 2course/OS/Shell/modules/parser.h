#ifndef PARSER_H
#define PARSER_H

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
  char *value;
  struct Node *left;
  struct Node *right;
  bool subshell;
  bool isOperator;
  bool isDaemon;
} Node;

char *trimStr(const char *str);
Node *createNode(const char *value);
bool isOperator(const char ch);
Node *parseExpressionInterface(const char *expression, int start, int end);
Node *parseExpression(const char *expression);
void printPreorder(Node *root, int i);
void freeTree(Node *root);

#endif