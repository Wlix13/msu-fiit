#include "list.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
  Node *head = create_list();

  // Hand created list
  Node *head2 = malloc(sizeof(Node));
  head2->data = 1;
  head2->next = malloc(sizeof(Node));
  head2->next->data = 2;
  head2->next->next = malloc(sizeof(Node));
  head2->next->next->data = 3;
  head2->next->next->next = NULL;

  printf("List: \n");
  print_list(head);
  printf("Mean: %f\n", mean(head));

  Node *new = merge_lists(head, head2);
  print_list(new);
  del_list(&new);
  del_list(&head);
  del_list(&head2);

  return 0;
}