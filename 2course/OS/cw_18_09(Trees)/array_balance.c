/*
Реализация балансировки бинарного дерева поиска методом разделения массива
на две части. Первая часть - левое поддерево, вторая - правое. Корень - средний
элемент массива. Далее рекурсивно строим левое и правое поддерево из левой и
правой части массива соответственно.
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int data;
  struct Node *left;
  struct Node *right;
} Node;

// Create a new node
Node *newNode(int data) {
  Node *node = (Node *)malloc(sizeof(Node));
  node->data = data;
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

// Store nodes of given BST in sorted order
void storeNodes(Node *node, Node *nodes[], int *index_ptr) {
  if (node == NULL) {
    return;
  }
  //   Left subtree
  storeNodes(node->left, nodes, index_ptr);
  //   Current node
  nodes[*index_ptr] = node;
  (*index_ptr)++;
  //   Right subtree
  storeNodes(node->right, nodes, index_ptr);
}

// Convert sorted array to balanced BST
Node *sortedArrayToTree(Node *nodes[], int start, int end) {
  if (start > end) {
    return NULL;
  }

  // Get the middle element and make it node
  int mid = (start + end) / 2;
  Node *node = nodes[mid];

  //  Construct the left subtree and make it left child of node
  node->left = sortedArrayToTree(nodes, start, mid - 1);

  //  Construct the right subtree and make it right child of node
  node->right = sortedArrayToTree(nodes, mid + 1, end);

  return node;
}

// Balance a binary search tree
// First, store nodes of given BST in sorted order in an array
// Then, build a balanced BST from the array
Node *balanceTree(Node *node) {
  Node *nodes[1000]; // Assuming that the tree has no more than 1000 nodes
  int n = 0;         // Number of nodes in the tree
  storeNodes(node, nodes, &n);
  return sortedArrayToTree(nodes, 0, n - 1);
}

int main() {
  Node *Tree = NULL;
  int x;

  printf("Enter tree nodes:\n");
  while (scanf("%d", &x) != EOF) {
    Tree = insertNode(Tree, x);
  }

  printf("Tree:\n");
  descriptivePrint(Tree);
  printf("\n");

  Tree = balanceTree(Tree);

  printf("Balanced tree:\n");
  descriptivePrint(Tree);
  printf("\n");

  cleanTree(Tree);

  return 0;
}
