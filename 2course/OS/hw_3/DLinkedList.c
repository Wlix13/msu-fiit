/*
Работа с двунаправленным списком, элемент данных - строка (char *).

Должны быть написаны:
1) Функция создания двунаправленного списка.
2) Функция удаления списка.
3) Функция вывода списка на экран.
4) Функция удаления элемента по заданному номеру (номер элемента запрашивается
со стандартного ввода).
5) Функция вставки элемента после элемента с заданным номером (номер элемента
запрашивается со стандартного ввода).

Вызов функций 3, 4, 5 должен быть организован в цикле с использованием массива
указателей на функции. Признак выхода из цикла — на ваше усмотрение.

В main() - список создается (вводится последовательность слов со стандартного
ввода), выводится в прямом и в обратном порядке, в цикле обрабатывается, вся
динамически выделенная память освобождается.
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  char *data;
  struct Node *next;
  struct Node *prev;
} Node;

Node *createNode(char *data) {
  Node *node = (Node *)malloc(sizeof(Node));
  node->data = data;
  node->next = NULL;
  node->prev = NULL;
  return node;
}

Node *createList() {
  Node *head = NULL;
  Node *tail = NULL;
  char *data = NULL;
  while (1) {
    printf("Enter data: ");
    scanf("%ms", &data);
    if (data[0] == '\0') {
      break;
    }
    Node *node = createNode(data);
    if (head == NULL) {
      head = node;
      tail = node;
    } else {
      tail->next = node;
      node->prev = tail;
      tail = node;
    }
  }
  return head;
}

void printList(Node *head) {
  Node *node = head;
  while (node != NULL) {
    printf("%s ", node->data);
    node = node->next;
  }
  printf("\n");
}

void printListReverse(Node *tail) {
  Node *node = tail;
  while (node != NULL) {
    printf("%s ", node->data);
    node = node->prev;
  }
  printf("\n");
}

void deleteList(Node *head) {
  Node *node = head;
  while (node != NULL) {
    Node *next = node->next;
    free(node->data);
    free(node);
    node = next;
  }
}

void deleteNode(Node *node) {
  if (node->prev != NULL) {
    node->prev->next = node->next;
  }
  if (node->next != NULL) {
    node->next->prev = node->prev;
  }
  free(node->data);
  free(node);
}

void deleteNodeByIndex(Node *head, int index) {
  Node *node = head;
  for (int i = 0; i < index; i++) {
    node = node->next;
  }
  deleteNode(node);
}

void insertNode(Node *node, char *data) {
  Node *newNode = createNode(data);
  newNode->next = node->next;
  newNode->prev = node;
  node->next = newNode;
  if (newNode->next != NULL) {
    newNode->next->prev = newNode;
  }
}

void insertNodeByIndex(Node *head, int index, char *data) {
  Node *node = head;
  for (int i = 0; i < index; i++) {
    node = node->next;
  }
  insertNode(node, data);
}

int main() {
  Node *head = createList();
  printList(head);
  printListReverse(head);
  deleteList(head);

  return 0;
}