#ifndef UTILS_H
#define UTILS_H

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define WRITE_END 1
#define READ_END 0

extern int DEBUG;
extern int maxFD;

void closeIrrelevantFDs(int exceptions[]);

char **tokenizeCommand(const char *command, int *numArgs);

#endif