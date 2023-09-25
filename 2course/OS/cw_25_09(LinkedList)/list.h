// Header file for linked list

#ifndef _list_h_

#define _list_h_

typedef struct Node {
  char *word;
  int length;
  struct Node *next;
} Node;

typedef struct Temp {
  char letter;
  struct Temp *next;
} Temp;

Node *createNode(char *, int);
Node *appendNode(Node *, char *, int);
Temp *appendTemp(Temp *, char);
void convertTempToNode(Node **, Temp **);
void freeList(Node **);
void freeTemp(Temp **);
void printList(Node *);
void MergeSort(struct Node **);

#endif
