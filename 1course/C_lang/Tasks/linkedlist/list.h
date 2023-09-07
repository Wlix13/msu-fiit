// Header file for linked list

#ifndef _list_h_

#define _list_h_

typedef struct Node {
  int data;
  struct Node *next;
} Node;

Node *create_list();
void del_list(Node **);
void del_last(Node **);
void print_list(Node *);
double mean(Node *);
int check_list(Node *);
Node *merge_lists(Node *, Node *);

#endif
