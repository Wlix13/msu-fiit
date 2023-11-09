/*
Написать функцию реверсирования однонаправленного списка (элемент данных — можно
сделать любой). Параметр функции — указатель на начало однонаправленного списка.
Нужно реверсировать список за один проход. Дополнительный список создавать
нельзя. Вернуть указатель на начало измененного списка.

В main() - список создается, выводится на экран, в цикле обрабатывается, снова
выводится. Вся динамически выделенная память освобождается.
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  char *data;
  struct Node *next;
} Node;

Node *createNode(char *data) {
  Node *newNode = (Node *)malloc(sizeof(Node));

  newNode->data = data;
  newNode->next = NULL;

  return newNode;
}

void appendNode(Node *head, char *data) {
  Node *current = head;

  while (current->next != NULL) {
    current = current->next;
  }

  current->next = createNode(data);
}

Node *reverse(Node *head) {
  Node *prev = NULL;
  Node *current = head;
  Node *next = NULL;

  while (current != NULL) {
    next = current->next;
    current->next = prev;
    prev = current;
    current = next;
  }

  return prev;
}

void printList(Node *list) {
  Node *current = list;

  while (current) {
    printf("%s -> ", current->data);
    current = current->next;
  }
  printf("NULL\n");
}

void freeList(Node *head) {
  Node *current = head;
  Node *next = NULL;

  while (current != NULL) {
    free(current->data);
    next = current->next;
    free(current);
    current = next;
  }
}

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

int main() {
  Node *head = NULL;

  printf("Enter words (one word per line, end with EOF):\n");
  char *word;
  while ((word = inputString()) && *word) {
    if (head == NULL) {
      head = createNode(word);
    } else {
      appendNode(head, word);
    }
  }

  // Clear last word
  if (word != NULL) {
    free(word);
  }

  printf("Original list:\n");
  printList(head);

  printf("Reversed list:\n");
  head = reverse(head);
  printList(head);

  freeList(head);

  return 0;
}