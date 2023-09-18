/*
1) Написать функцию создания двоичного дерева. Тип хранимых данных - int
Числа поступаю со стандратного входа до возникновения "конца файла"

2) Написать функцию вывода на экран двоичного дерева

3) Написать функцию удаления дерева

4) Написать функцию, определяющую, входит ли элемент в дерево

5) Если входит, вернуть длину пути (количество узлов) до ближайшего узла,
содержащего данный элемент, в случае, если это корень - результат равен 0. Если
элемент не найден, вернуть - 1.

6) Написать функцию удаления узла дерева(сдвинуть узлы вверх, на место
удалённого)
*/

#include "stdio.h"
#include "stdlib.h"

typedef struct Node {
  int data;
  struct Node *left;
  struct Node *right;
} Node;

Node *add_leaf(Node *T, int x) {
  if (T == NULL) {
    T = malloc(sizeof(Node));
    T->data = x;
    T->left = NULL;
    T->right = NULL;
  } else {
    if (T->data > x) {
      T->left = add_leaf(T->left, x);
    } else {
      T->right = add_leaf(T->right, x);
    }
  };
  return T;
}

void print_tree(Node *T) {
  if (T != NULL) {
    print_tree(T->left);
    printf("%d ", T->data);
    print_tree(T->right);
  }
}

void clean_tree(Node *T) {
  if (T != NULL) {
    clean_tree(T->left);
    clean_tree(T->right);
    free(T);
  }
}

int check_tree(Node *T, int x) {
  if (T == NULL) {
    return 0;
  }
  if (T->data == x) {
    return 1;
  }
  if (T->data > x) {
    return check_tree(T->left, x);
  } else {
    return check_tree(T->right, x);
  }
}

int check_tree_count(Node *T, int x) {
  if (T == NULL) {
    return -1;
  }
  if (T->data == x) {
    return 0;
  }
  if (T->data > x) {
    int count = check_tree_count(T->left, x);
    if (count == -1) {
      return -1;
    } else {
      return count + 1;
    }
  } else {
    int count = check_tree_count(T->right, x);
    if (count == -1) {
      return -1;
    } else {
      return count + 1;
    }
  }
}

Node *minValueNode(Node *T) {
  Node *current = T;
  while (current->left != NULL) {
    current = current->left;
  }
  return current;
}

Node *del_node_tree(Node *T, int data) {
  if (T == NULL) {
    return T;
  }
  //   Find the node to be deleted
  if (data < T->data) {
    T->left = del_node_tree(T->left, data);
  } else if (data > T->data) {
    T->right = del_node_tree(T->right, data);
  } else {
    // If left or right child is NULL
    if (T->left == NULL) {
      Node *temp = T->right;
      free(T);
      return temp;
    } else if (T->right == NULL) {
      Node *temp = T->left;
      free(T);
      return temp;
    }

    // If both children exist
    // Find the inorder successor
    Node *temp = minValueNode(T->right);
    T->data = temp->data;
    T->right = del_node_tree(T->right, temp->data);
  }
  return T;
}

int main() {
  Node *T = NULL;
  int x;

  while (scanf("%d", &x) != EOF) {
    T = add_leaf(T, x);
  }

  printf("Tree:\n");
  print_tree(T);
  printf("\n");

  //  Check if number in tree
  int num_find = 5;
  printf("Is number `%d` in tree: %d\n", num_find, check_tree(T, 5));
  printf("Nodes before number `%d` node: %d\n", num_find,
         check_tree_count(T, 5));

  // Remove node(number) from tree
  int num_del = 5;
  T = del_node_tree(T, num_del);
  printf("Node after removing number `%d`:\n", num_del);
  print_tree(T);
  printf("\n");

  clean_tree(T);
  return 0;
}