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

/*
 * Function to trim leading and trailing whitespace from string
 * @param str: The string to be trimmed
 * @return A pointer to the trimmed string
 */
char *trimStr(const char *str);

/*
 * Function to create a new node for binary tree
 * @param value: The value of the node
 * @return A pointer to the new node
 */
Node *createNode(const char *value);

/*
 * Function to check if character is an operator (|, >, <, &, ;)
 * @param ch: The character to be checked
 * @return true if the character is an operator, false otherwise
 */
bool isOperator(const char ch);

/*
 * Interface to parse expression
 * @param expression: The expression to be parsed
 * @param start: The start index of the expression
 * @param end: The end index of the expression
 * @return A pointer to the root of the binary tree
 */
Node *parseExpressionInterface(const char *expression, int start, int end);

/*
 * Function to parse expression
 * @param expression: The expression to be parsed
 * @return A pointer to the root of the binary tree
 */
Node *parseExpression(const char *expression);

/*
 * Function to print binary tree in preorder
 * @param root: The root of binary tree
 * @param i: The index of the node
 */
void printPreorder(Node *root, int i);

/*
 * Function to free binary tree
 * Arguments:
 *   root: The root of binary tree
 */
void freeTree(Node *root);

#endif