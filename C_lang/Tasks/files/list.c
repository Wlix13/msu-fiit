/*

Custom library to handle linked lists(withou memory leaks)

1) create_node() - creates a linked list with first element
2) add_node() - adds node to linked list
3) del_list() - deletes the linked list
4) print_list() - prints the linked list
copies of links of the original lists.
*/

#include "list.h"
#include <stdio.h>
#include <stdlib.h>

/*
Function to create a linked list with first element
Return:
    `Node *` - pointer to the head of the linked list
*/
Node *create_node(char data) {
  Node *new_node = (Node *)malloc(sizeof(Node));
  new_node->data = data;
  new_node->next = NULL;
  return new_node;
}

/*
Function to add node to linked list
Parameters:
    `head` - pointer to the head of the linked list
    `data` - data to be added to the linked list
Return:
    `Node *` - pointer to the head of the linked list
*/
void add_node(Node **head, char data) {
  Node *new_node = create_node(data);
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

/*
Function to delete the linked list
Parameters:
    `head` - pointer to the head of the linked list
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
    `head` - pointer to the head of the linked list
Return:
    'void'
*/
void print_list(Node *head) {
  Node *current = head;
  if (current == NULL) {
    printf("Empty list\n");
    return;
  }
  while (current != NULL) {
    printf("%c ", current->data);
    current = current->next;
  }
  printf("\n");
}
