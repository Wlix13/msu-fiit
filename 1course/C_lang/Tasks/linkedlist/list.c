/*

Custom library to handle linked lists(withou memory leaks)

1) create_list() - creates a linked list from the input stream
2) del_list() - deletes the linked list
3) print_list() - prints the linked list
4) mean() - calculates the mean of the linked list
5) del_last() - deletes last element of the linked list
6) check_list() - checks if the linked list is non-decreasing
7) merge_lists() - receives two ordered lists and returns NEW ordered list, from
copies of links of the original lists.
*/

#include "list.h"
#include <stdio.h>
#include <stdlib.h>

/*
Function to create a linked list from the input stream
Return:
    `Node *` - pointer to the head of the linked list
*/
Node *create_list() {
  Node *head = NULL;
  Node *current = NULL;
  Node *previous = NULL;
  int data;
  while (scanf("%d", &data) == 1) {
    current = (Node *)malloc(sizeof(Node));
    current->data = data;
    current->next = NULL;
    if (previous != NULL) {
      previous->next = current;
    } else {
      head = current;
    }
    previous = current;
  }
  return head;
}

/*
Function to delete the linked list
Parameters:
    head - pointer to the head of the linked list
Return:
    'void'
*/
void del_list(Node **head) {
  Node *current = *head;
  Node *next;
  while (current != NULL) {
    next = current->next;
    free(current);
    current = next;
  }
  *head = NULL;
}

/*
Function to print the linked list
Parameters:
    head - pointer to the head of the linked list
Return:
    'void'
*/
void print_list(Node *head) {
  Node *current = head;
  if (current == NULL) {
    printf("Empty list");
    return;
  }
  while (current != NULL) {
    printf("%d ", current->data);
    current = current->next;
  }
  printf("\n");
}

/*
Function to caclulate the mean of the linked list
Parameters:
    head - pointer to the head of the linked list
Return:
    'double' - mean of the linked list
*/
double mean(Node *head) {
  Node *current = head;
  double sum = 0;
  int count = 0;
  while (current != NULL) {
    sum += current->data;
    count++;
    current = current->next;
  }
  return sum / count;
}

/*
Function to delete tlast element of the linked list
Parameters:
    head - pointer to the head of the linked list
Return:
    'void'
*/
void del_last(Node **head) {
  Node *current = *head;
  Node *previous = NULL;
  while (current->next != NULL) {
    previous = current;
    current = current->next;
  }
  free(current);
  previous->next = NULL;
}

/*
Function to check if the linked list is non-decreasing
Parameters:
    head - pointer to the head of the linked list
Return:
    'int' - 1 if the linked list is non-decreasing, 0 otherwise
*/

int check_list(Node *head) {
  Node *current = head;
  while (current->next != NULL) {
    if (current->data > current->next->data)
      return 0;
    current = current->next;
  }
  return 1;
}

/*
Function to receive two ordered lists and returns NEW ordered list, from copies
of links of the original lists.
Parameters: head1 - pointer to the head of the first linked list
    head2 - pointer to the head of the second linked list
Return:
    'Node *' - pointer to the head of the new linked list
*/
Node *merge_lists(Node *l1, Node *l2) {
  Node *head = NULL;
  Node **tail = &head;

  while (l1 && l2) {
    *tail = malloc(sizeof(Node));
    if (l1->data <= l2->data) {
      (*tail)->data = l1->data;
      (*tail)->next = NULL;
      l1 = l1->next;
    } else {
      (*tail)->data = l2->data;
      (*tail)->next = NULL;
      l2 = l2->next;
    }
    tail = &(*tail)->next;
  }
  while (l1) {
    *tail = malloc(sizeof(Node));
    (*tail)->data = l1->data;
    (*tail)->next = NULL;
    l1 = l1->next;
    tail = &(*tail)->next;
  }
  while (l2) {
    *tail = malloc(sizeof(Node));
    (*tail)->data = l2->data;
    (*tail)->next = NULL;
    l2 = l2->next;
    tail = &(*tail)->next;
  }

  return head;
}
