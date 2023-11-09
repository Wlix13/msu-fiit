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
#include <string.h>

typedef struct Node {
  char *data;
  struct Node *prev;
  struct Node *next;
} Node;

typedef struct DoublyLinkedList {
  Node *head;
  Node *tail;
} DoublyLinkedList;

char *inputString() {
  char *str;
  int ch;
  long size = 10;
  long len = 0;
  str = (char *)malloc(size);

  while ((ch = getchar()) != EOF && ch != '\n') {
    str[len++] = ch;
    if (len == size) {
      size *= 2;
      str = (char *)realloc(str, size);
    }
  }
  str[len++] = '\0';

  char *tmp = realloc(str, len);
  if (tmp == NULL) {
    free(str);
    return NULL;
  } else {
    str = tmp;
  }

  return str;
}

DoublyLinkedList *createList() {
  DoublyLinkedList *list = (DoublyLinkedList *)malloc(sizeof(DoublyLinkedList));
  list->head = NULL;
  list->tail = NULL;
  return list;
}

void freeList(DoublyLinkedList *list) {
  Node *current = list->head;
  while (current) {
    Node *next = current->next;
    free(current->data);
    free(current);
    current = next;
  }
  free(list);
}

void printList(DoublyLinkedList *list) {
  Node *current = list->head;
  while (current) {
    printf("%s -> ", current->data);
    current = current->next;
  }
  printf("NULL\n");
}

void printListReverse(DoublyLinkedList *list) {
  Node *current = list->tail;
  while (current) {
    printf("%s -> ", current->data);
    current = current->prev;
  }
  printf("NULL\n");
}

void deleteNodeByIndex(DoublyLinkedList *list) {
  int index;
  printf("Enter position to delete: ");
  scanf("%d", &index);

  if (!list->head)
    return;

  Node *current = list->head;
  for (int i = 0; i < index && current; i++) {
    current = current->next;
  }

  if (!current)
    return;

  if (current->prev) {
    current->prev->next = current->next;
  } else {
    list->head = current->next;
  }

  if (current->next) {
    current->next->prev = current->prev;
  } else {
    list->tail = current->prev;
  }

  free(current->data);
  free(current);
}

void insertNodeAfterIndex(DoublyLinkedList *list) {
  int index;
  char data[128 + 1];
  printf("Enter position to insert after: ");
  scanf("%d", &index);
  printf("Enter string to insert: ");
  scanf("%s", data);

  Node *newNode = (Node *)malloc(sizeof(Node));
  newNode->data = strdup(data);
  newNode->prev = NULL;
  newNode->next = NULL;

  if (!list->head) {
    list->head = newNode;
    list->tail = newNode;
    return;
  }

  Node *current = list->head;
  for (int i = 0; i < index && current; i++) {
    current = current->next;
  }

  if (!current) {
    list->tail->next = newNode;
    newNode->prev = list->tail;
    list->tail = newNode;
  } else {
    newNode->next = current->next;
    newNode->prev = current;
    if (current->next) {
      current->next->prev = newNode;
    } else {
      list->tail = newNode;
    }
    current->next = newNode;
  }
}

void insertNodeAtBeginning(DoublyLinkedList *list, char *data) {
  Node *newNode = (Node *)malloc(sizeof(Node));
  newNode->data = strdup(data);
  newNode->prev = NULL;
  newNode->next = list->head;

  if (list->head) {
    list->head->prev = newNode;
  } else {
    list->tail = newNode;
  }

  list->head = newNode;
}

int main() {
  void (*functions[])(DoublyLinkedList *) = {
      printList,
      deleteNodeByIndex,
      insertNodeAfterIndex,
  };

  DoublyLinkedList *head = createList();

  printf("Enter words (one word per line, end with EOF):\n");
  char *word;
  while ((word = inputString()) && *word) {
    insertNodeAtBeginning(head, word);
    free(word);
  }
  // Clear last word
  if (word != NULL) {
    free(word);
  }

  // Summon flying menu
  int choice = 1;
  while (choice != 0) {
    printf("\nMenu:\n");
    printf("1. Print list\n");
    printf("2. Delete node by index\n");
    printf("3. Insert node after index\n");
    printf("0. Exit\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    if (choice >= 1 && choice <= 3) {
      functions[choice - 1](head);
    }
  };

  freeList(head);

  return 0;
}
