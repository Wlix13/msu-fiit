/*
Реализация балансировки бинарного дерева поиска методом вращения (AVL-дерево).
Каждый узел дерева имеет два поля: ключ и высоту поддерева с корнем в этом узле.
Высота пустого дерева равна 0. Высота непустого дерева равна максимальной высоте
его поддеревьев + 1. Для каждого узла высота левого и правого поддеревьев может
отличаться не более чем на 1. Если это условие нарушается, то дерево
перебалансировывается путем вращения. Вращение выполняется в том случае, если
высота одного поддерева больше высоты другого поддерева на 2.
Есть 4 случая вращения
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int height;
  int data;
  struct Node *left;
  struct Node *right;
} Node;

int max(int a, int b) { return (a > b) ? a : b; }

int getHeight(Node *node) {
  if (node == NULL) {
    return 0;
  }
  return node->height;
}

// Count balance factor of node
int getBalance(Node *node) {
  if (node == NULL) {
    return 0;
  }
  return getHeight(node->left) - getHeight(node->right);
}

// Right rotate subtree nodeed with y
Node *rightRotate(Node *y) {
  Node *x = y->left;
  Node *T2 = x->right;

  // Perform rotation
  x->right = y;
  y->left = T2;

  // Recount heights
  y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
  x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

  return x;
}

// Left rotate subtree nodeed with x
Node *leftRotate(Node *x) {
  Node *y = x->right;
  Node *T2 = y->left;

  // Perform rotation
  y->left = x;
  x->right = T2;

  // Recount heights
  x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
  y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

  return y;
}

// Create a new node
Node *newNode(int data) {
  Node *node = (Node *)malloc(sizeof(Node));
  node->data = data;
  node->height = 1; // Every new node initially is a leaf
  node->left = NULL;
  node->right = NULL;
  return node;
}

// Insert a new node with given data to Tree
Node *insertNode(Node *node, int data) {
  if (node == NULL) {
    return newNode(data);
  }

  if (data < node->data) {
    node->left = insertNode(node->left, data);
  } else if (data > node->data) {
    node->right = insertNode(node->right, data);
  } else {
    return node; // Without duplicates
  }

  // Get new height of node and count balance factor
  node->height = 1 + max(getHeight(node->left), getHeight(node->right));
  int balance = getBalance(node);

  // Left-Left Case
  if (balance > 1 && data < node->left->data) {
    return rightRotate(node);
  }

  // Right-Right Case
  if (balance < -1 && data > node->right->data) {
    return leftRotate(node);
  }

  // Left-Right Case
  if (balance > 1 && data > node->left->data) {
    node->left = leftRotate(node->left);
    return rightRotate(node);
  }

  // Right-Left Case
  if (balance < -1 && data < node->right->data) {
    node->right = rightRotate(node->right);
    return leftRotate(node);
  }

  return node;
}

// Free memory allocated for the tree
void cleanTree(Node *node) {
  if (node != NULL) {
    cleanTree(node->left);
    cleanTree(node->right);
    free(node);
  }
}

// Print tree in inorder way
void basicPrint(Node *node) {
  if (node != NULL) {
    basicPrint(node->left);
    printf("%d ", node->data);
    basicPrint(node->right);
  }
}

// Print tree in a way, when each node is printed with its children
// Node: ..., Left: ..., Right: ...
void descriptivePrint(Node *node) {
  if (node != NULL) {
    printf("Node: %d", node->data);
    if (node->left != NULL) {
      printf(", Left: %d", node->left->data);
    } else {
      printf(", Left: NULL");
    }
    if (node->right != NULL) {
      printf(", Right: %d\n", node->right->data);
    } else {
      printf(", Right: NULL\n");
    }
    descriptivePrint(node->left);
    descriptivePrint(node->right);
  }
}

int main() {
  Node *Tree = NULL;
  int x;

  while (scanf("%d", &x) != EOF) {
    Tree = insertNode(Tree, x);
  }

  printf("Tree after insertion:\n");
  descriptivePrint(Tree);
  printf("\n");

  cleanTree(Tree);

  return 0;
}
