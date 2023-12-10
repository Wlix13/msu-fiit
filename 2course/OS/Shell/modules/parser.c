#include "parser.h"

/*
 * Function to trim leading and trailing whitespace from string
 * @param str: The string to be trimmed
 * @return A pointer to the trimmed string
 */
char *trimStr(const char *str) {
  size_t strLength = strlen(str);
  const char *start = str;
  const char *end = str + strLength - 1;

  while (isspace((unsigned char)*start))
    ++start;
  while (end > start && isspace((unsigned char)*end))
    --end;

  size_t trimmedLength = end - start + 1;
  char *trimmedStr = malloc(trimmedLength + 1);
  if (trimmedStr != NULL) {
    memcpy(trimmedStr, start, trimmedLength);
    trimmedStr[trimmedLength] = '\0';
  }

  return trimmedStr;
}

/*
 * Function to create a new node for binary tree
 * @param value: The value of the node
 * @return A pointer to the new node
 */
Node *createNode(const char *value) {
  Node *newNode = (Node *)malloc(sizeof(Node));
  newNode->value = strdup(value);
  newNode->left = NULL;
  newNode->right = NULL;
  newNode->subshell = false;
  newNode->isOperator = true;
  newNode->isDaemon = false;
  return newNode;
}

/*
 * Function to check if character is an operator (|, >, <, &, ;)
 * @param ch: The character to be checked
 * @return true if the character is an operator, false otherwise
 */
bool isOperator(const char ch) {
  return (ch == '|' || ch == '>' || ch == '<' || ch == '&' || ch == ';');
}

/*
 * Interface to parse expression
 * @param expression: The expression to be parsed
 * @param start: The start index of the expression
 * @param end: The end index of the expression
 * @return A pointer to the root of the binary tree
 */
Node *parseExpressionInterface(const char *expression, int start, int end) {
  if (start > end)
    return NULL;

  Node *root = NULL;
  int operatorCount = 0;
  int bracketCount = 0;

  for (int i = end; i >= start; i--) {
    if (expression[i] == '(')
      bracketCount--;
    else if (expression[i] == ')')
      bracketCount++;

    if (bracketCount > 0)
      continue;

    if (bracketCount == 0 && !isOperator(expression[i]))
      if (i - 1 >= start)
        continue;

    operatorCount++;

    if (expression[i] == ';' && operatorCount == 1) {
      root = createNode(";");
      root->left = parseExpressionInterface(expression, start, i - 1);
      root->right = parseExpressionInterface(expression, i + 1, end);
      break;
    } else if (expression[i] == '&' && operatorCount == 1) {
      // If the previous character is also &, it is &&(AND)
      if (i - 1 >= start && expression[i - 1] == '&') {
        root = createNode("&&");
        root->left = parseExpressionInterface(expression, start, i - 2);
      } else {
        // Otherwise, it is just &(background)
        root = createNode("&");
        root->left = parseExpressionInterface(expression, start, i - 1);
      }

      root->right = parseExpressionInterface(expression, i + 1, end);

      break;
    } else if (expression[i] == '|' && operatorCount == 1) {
      // If the previous character is also |, it is ||(OR)
      if (i - 1 >= start && expression[i - 1] == '|') {
        root = createNode("||");
        root->left = parseExpressionInterface(expression, start, i - 2);
      } else {
        // Otherwise, it is just |(pipe)
        root = createNode("|");
        root->left = parseExpressionInterface(expression, start, i - 1);
      }

      root->right = parseExpressionInterface(expression, i + 1, end);

      break;
    } else if ((expression[i] == '>' || expression[i] == '<') &&
               operatorCount == 1) {
      // If the previous character is also >, it is >>(append)
      if (i - 1 >= start && expression[i - 1] == expression[i]) {
        if (expression[i] == '>')
          root = createNode(">>");
        else
          root = createNode("<<");

        root->left = parseExpressionInterface(expression, start, i - 2);
        root->right = parseExpressionInterface(expression, i + 1, end);
      } else {
        // Otherwise, it is just >(write)
        if (expression[i] == '>')
          root = createNode(">");
        else
          root = createNode("<");

        root->left = parseExpressionInterface(expression, start, i - 1);
        root->right = parseExpressionInterface(expression, i + 1, end);
      }
      break;
    }
  }

  // If no operator found, it is a command
  if (root == NULL) {
    char *str = trimStr(strndup(&expression[start], end - start + 1));

    // Check if the command is daemonized(subshell)
    if (str[0] == '(' && str[strlen(str) - 1] == ')') {
      root = parseExpressionInterface(str, 1, strlen(str) - 2);
      root->subshell = true;
    } else {
      root = createNode(str);
      root->isOperator = false;
    }
    free(str);
  }

  return root;
}

/*
 * Function to parse expression
 * @param expression: The expression to be parsed
 * @return A pointer to the root of the binary tree
 */
Node *parseExpression(const char *expression) {
  int len = strlen(expression);
  Node *root = parseExpressionInterface(expression, 0, len - 1);

  return root;
}

/*
 * Function to print binary tree in preorder
 * @param root: The root of binary tree
 * @param i: The index of the node
 */
void printPreorder(Node *root, int i) {
  if (root) {
    printf("%s %d [subshell: %s]\n", root->value, i++,
           root->subshell ? "True" : "False");
    printPreorder(root->left, i);
    printPreorder(root->right, i);
  }
}

/*
 * Function to free binary tree
 * Arguments:
 *   root: The root of binary tree
 */
void freeTree(Node *root) {
  if (root) {
    freeTree(root->left);
    freeTree(root->right);
    free(root->value);
    free(root);
  }
}
