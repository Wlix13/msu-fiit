#include "parser.h"

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

bool isOperator(const char ch) {
  return (ch == '|' || ch == '>' || ch == '<' || ch == '&' || ch == ';');
}

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

Node *parseExpression(const char *expression) {
  int len = strlen(expression);
  Node *root = parseExpressionInterface(expression, 0, len - 1);

  return root;
}

void printPreorder(Node *root, int i) {
  if (root) {
    printf("%s %d [subshell: %s]\n", root->value, i++,
           root->subshell ? "True" : "False");
    printPreorder(root->left, i);
    printPreorder(root->right, i);
  }
}

void freeTree(Node *root) {
  if (root) {
    freeTree(root->left);
    freeTree(root->right);
    free(root->value);
    free(root);
  }
}
