#include "list.h"
#include <stdio.h>
#include <stdlib.h>

/*
Rewrite the contents of the first file into the second one, adding line
number at the start of each line(read by char)
*/
void copy(FILE *ffrom, FILE *fto) {
  char c;
  int line = 1;
  while ((c = fgetc(ffrom)) != EOF) {
    if (line == 1) {
      fprintf(fto, "%d. ", line);
    }
    fprintf(fto, "%c", c);
    if (c == '\n') {
      line++;
      fprintf(fto, "%d. ", line);
    }
  }
}

/*
Remove empty lines from the file
*/
void remove_empty_lines(FILE *ffrom, FILE *fto) {
  char ch;
  int blank_line = 1;
  while ((ch = fgetc(ffrom)) != EOF) {
    if (ch == '\n') {
      if (!blank_line) {
        fputc('\n', fto);
      }
      blank_line = 1;
    } else if (ch != '\r' && ch != ' ' && ch != '\t') {
      blank_line = 0;
      fputc(ch, fto);
    }
  }
}

/*
Make a linked list of the first characters of all non-empty lines of the
file. If the file is empty or contains only empty lines, the list must be
empty.
*/
Node *first_chars(FILE *ffrom, Node *head) {
  int new_line_flag = 1;
  char c;
  while ((c = getc(ffrom)) != EOF) {
    if (new_line_flag && c != '\n') {
      add_node(&head, c);
      new_line_flag = 0;
    }
    if (c == '\n') {
      new_line_flag = 1;
    }
  }
  return head;
}

/*
Write in the file with the last line all the elements of the list constructed in
first_chars
*/
void save_list(FILE *fto, Node *head) {
  Node *current = head;
  fprintf(fto, "\n");
  while (current != NULL) {
    fprintf(fto, "%c", current->data);
    current = current->next;
  }
  fclose(fto);
}

/*
Program that, when started, gets the names of two text files on the command
line.
*/
int main(int argc, char **argv) {
  FILE *ffrom, *fto;
  if (argc != 3) {
    fprintf(stderr, "Usage: copy <from> <to>\n");
    return 1;
  }

  if ((ffrom = fopen(argv[1], "r")) == NULL) {
    fprintf(stderr, "Can't open %s\n", argv[1]);
    return 1;
  }

  if ((fto = fopen(argv[2], "w")) == NULL) {
    fprintf(stderr, "Can't open %s\n", argv[2]);
    return 1;
  }

  if (!ffrom || !fto) {
    fprintf(stderr, "Couldn't open files\n");
    return 1;
  }

  copy(ffrom, fto);

  remove_empty_lines(ffrom, fto);

  Node *head = first_chars(ffrom, NULL);
  print_list(head);

  save_list(fto, head);

  del_list(&head);
  fclose(ffrom);
  fclose(fto);
}