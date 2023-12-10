#include "modules/operators.h"
#include "modules/parser.h"
#include "modules/pipes.h"
#include "modules/process.h"
#include "modules/utils.h"

void quitHandler() { exit(0); }

// Sample: (cat a.txt && (wc -l < file1.txt || echo "Error calculating line
// count")) | tee output.txt | wc -w
int main() {
  signal(SIGQUIT, quitHandler);

  // Enable DEBUG mode if DEBUG is set( like DEBUG=1 ./shell)
  char *debugEnv = getenv("DEBUG");
  if (debugEnv != NULL) {
    DEBUG = atoi(debugEnv);
  } else {
    DEBUG = 0; // Default value if DEBUG is not set
  }

  while (1) {
    printf("\n> ");
    fflush(stdout);

    int len;
    char c;
    char *str = malloc(sizeof(char));
    int count = 0;
    // Read input
    while ((len = read(STDIN_FILENO, &c, sizeof(char)))) {
      if (c == '\n')
        break;

      str[count++] = c;
      str = realloc(str, sizeof(char) * (count + 1));
    }

    // If EOF is read, exit
    if (!len) {
      free(str);
      break;
    }
    if (count == 0) {
      free(str);
      continue;
    }

    str = realloc(str, sizeof(char) * (count + 1));
    str[count] = '\0';

    if (!strcmp(str, "exit")) {
      free(str);
      break;
    }

    // Wait for children to finish
    while (waitpid(-1, NULL, WNOHANG) > 0) {
    }

    Node *root = parseExpression(str);

    if (DEBUG) {
      printf("Preorder expression: \n");
      printPreorder(root, 0);
    }

    processAndRun(root);

    freeTree(root);
    free(str);
  }

  // Kill leftover children
  signal(SIGQUIT, SIG_IGN);
  kill(0, SIGQUIT);

  // Wait for SIQUIT to be processed
  struct timespec sleep_time;
  sleep_time.tv_sec = 0;          // Seconds
  sleep_time.tv_nsec = 750000000; // Nanoseconds (0.5 seconds)
  nanosleep(&sleep_time, NULL);

  // Wait for defunct children
  while (waitpid(-1, NULL, WNOHANG) > 0) {
  }

  if (DEBUG)
    system("ps a");

  return 0;
}
