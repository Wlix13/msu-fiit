#include "utils.h"

int DEBUG = 0;
int maxFD = 2;

/*
 * Function to close all file descriptors except exceptions
 * @param exceptions - array of file descriptors to not close
 */
void closeIrrelevantFDs(int exceptions[]) {
  for (int fd = 0; fd <= maxFD; fd++) {
    int close_fd = 1;
    for (int i = 0; exceptions[i] != -1; i++) {
      if (fd == exceptions[i]) {
        close_fd = 0;
        break;
      }
    }

    if (close_fd)
      close(fd);
  }
}

/*
 * Function to tokenize(split) command into arguments
 * @param command - command to tokenize
 * @param numArgs - pointer to int to store number of arguments
 * @return array of arguments
 */
char **tokenizeCommand(const char *command, int *numArgs) {
  // Copy command to not modify it
  char *copy = strdup(command);

  char *token;
  int count = 0;
  char **args = malloc(sizeof(char *));

  // Get first token
  token = strtok(copy, " ");

  while (token != NULL) {
    args = realloc(args, (count + 1) * sizeof(char *));
    args[count] = strdup(token);
    token = strtok(NULL, " ");
    count++;
  }

  args = realloc(args, (count + 1) * sizeof(char *));
  args[count] = NULL;

  if (numArgs)
    *numArgs = count;

  free(copy);

  return args;
}