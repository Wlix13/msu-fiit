/*
1. Читать из стандартного ввода последовательность слов до появления конца
строки "In' или EOF. Слова разделяются пробелами (количество подряд идущих
пробелов
>=1), в начале и в конце строки пробелы тоже возможны, но их наличие не
обязательно. Длина строки и слов не ограничена. Пользоваться функцией realloc()
(и функцией ввода из дз-1) при вводе строки. нельзя, отрабатываем работу со
списками! Организовать хранение введенных данных, используя динамические
структуры данных (списки), поля в которых определяются по потребности, на ваше
усмотрение. Для хранения информации о длинах слов также использовать список.

2. Вывести на экран пары - слово и длина слова - в порядке убывания их длин.
В случае одинаковых длин, слова выводить в порядке их ввода.

3. Освободить всю динамически выделенную память.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
  char *word;
  int lenght;
  struct Node *next;
} Node;

typedef struct Temp {
  char word;
  struct Temp *next;
} Temp;

Node *createNode(char *word) {
  Node *node = (Node *)malloc(sizeof(Node));
  node->word = word;
  node->lenght = strlen(word);
  node->next = NULL;
  return node;
}

void addNode(Node **head, char *data) {
  Node *new_node = createNode(data);
  if (*head == NULL) {
    *head = new_node;
    return;
  }
  Node *current = *head;
  while (current->next != NULL) {
    current = current->next;
  }
  current->next = new_node;
}

void del_list(Node **head) {
  Node *current = *head;
  Node *next;
  while (current != NULL) {
    next = current->next;
    free(current->word);
    free(current);
    current = next;
  }
  *head = NULL;
}

void print_list(Node *head) {
  Node *current = head;
  while (current != NULL) {
    printf("%s - %d\n", current->word, current->lenght);
    current = current->next;
  }
}

void FrontBackSplit(Node *source, Node **frontRef, Node **backRef) {
  struct Node *fast; // Moves two times faster
  struct Node *slow;

  slow = source;
  fast = source->next;

  while (fast != NULL) {
    fast = fast->next;
    if (fast != NULL) {
      slow = slow->next;
      fast = fast->next;
    }
  }

  *frontRef = source;
  *backRef = slow->next;
  slow->next = NULL;
}

Node *SortedMerge(Node *a, Node *b) {
  struct Node *result = NULL;

  if (a == NULL) {
    return b;
  } else if (b == NULL) {
    return a;
  }

  if (a->lenght >= b->lenght) {
    result = a;
    result->next = SortedMerge(a->next, b);
  } else {
    result = b;
    result->next = SortedMerge(a, b->next);
  }
  return result;
}

void MergeSort(struct Node **headRef) {
  struct Node *head = *headRef;
  struct Node *a;
  struct Node *b;

  if ((head == NULL) || (head->next == NULL)) {
    return;
  }

  /* Split into 'a' and 'b' sublists */
  FrontBackSplit(head, &a, &b);

  /* Recursively sort sublists */
  MergeSort(&a);
  MergeSort(&b);

  *headRef = SortedMerge(a, b);
}

// Input string by chars to TempNode
Temp *inputString() {
  Temp *head = NULL;
  Temp *current = NULL;
  char c;
  while ((c = getchar()) != EOF && c != '\n') {
    if (head == NULL) {
      head = (Temp *)malloc(sizeof(Temp));
      head->word = c;
      head->next = NULL;
      current = head;
    } else {
      current->next = (Temp *)malloc(sizeof(Temp));
      current = current->next;
      current->word = c;
      current->next = NULL;
    }
  }
  return head;
}

Node *convertString(Temp *temp) {
  Node *head = NULL;
  Node *current = NULL;
  char *word = NULL;
  int i = 0;
  while (temp != NULL) {
    if (temp->word == ' ') {
      word[i] = '\0';
      addNode(&head, word);
      i = 0;
      free(word);
    } else {
      word[i] = temp->word;
      i++;
    }
    temp = temp->next;
  }
  return head;
}

// 12345678123456781234567812345678
int main() {
  Temp *temp = inputString();
  char c;

  Node *head = convertString(temp);

  print_list(head);
  //   MergeSort(&head);
  //   print_list(head);

  // del_list(&head);
  return 0;
}
