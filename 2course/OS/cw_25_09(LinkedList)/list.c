
#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Node *createNode(char *word, int length) {
  Node *newNode = (Node *)malloc(sizeof(Node));

  newNode->word = strdup(word);
  newNode->length = length;
  newNode->next = NULL;

  return newNode;
}

Node *appendNode(Node *head, char *word, int length) {
  if (head == NULL)
    return createNode(word, length);

  Node *current = head;
  while (current->next != NULL)
    current = current->next;

  current->next = createNode(word, length);

  return head;
}

/*
Create a new node, assign the letter to it, add it to the end of the
temporary list.
*/
Temp *appendTemp(Temp *head, char letter) {
  Temp *newTemp = (Temp *)malloc(sizeof(Temp));

  newTemp->letter = letter;
  newTemp->next = NULL;

  if (head == NULL)
    return newTemp;

  Temp *current = head;
  while (current->next != NULL)
    current = current->next;

  current->next = newTemp;

  return head;
}

/*
Convert temporary list into node in the main list. Calculate the length of
temporary list, create word from letters in the temporary list, append new node
with word to main list, and free the temporary list.
*/
void convertTempToNode(Node **head, Temp **tempHead) {
  int length = 0;
  Temp *current = *tempHead;
  while (current != NULL) {
    length++;
    current = current->next;
  }

  char *word = (char *)malloc(length + 1);
  current = *tempHead;
  for (int i = 0; i < length; i++) {
    word[i] = current->letter;
    current = current->next;
  }
  word[length] = '\0';

  *head = appendNode(*head, word, length);
  freeTemp(tempHead);
  free(word);
}

void freeList(Node **head) {
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

void freeTemp(Temp **head) {
  Temp *current = *head;
  Temp *next;
  while (current != NULL) {
    next = current->next;
    free(current);
    current = next;
  }
  *head = NULL;
}

void printList(Node *head) {
  Node *current = head;
  while (current != NULL) {
    printf("%s - %d\n", current->word, current->length);
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

  if (a->length >= b->length) {
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
