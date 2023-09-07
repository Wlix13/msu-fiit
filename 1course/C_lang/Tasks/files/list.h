// Header file for linked list

#ifndef _list_h_

#define _list_h_

typedef struct Node {
  char data;
  struct Node *next;
} Node;

Node *create_node(char);
void add_node(Node **, char);
void del_list(Node **);
void print_list(Node *);

#endif
