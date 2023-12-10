#ifndef UTILS_H
#define UTILS_H

#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define WRITE_END 1
#define READ_END 0

extern int DEBUG;
extern int maxFD;

/*
 * Function to close all file descriptors except exceptions
 * @param exceptions - array of file descriptors to not close
 */
void closeIrrelevantFDs(int exceptions[]);

/*
 * Function to tokenize(split) command into arguments
 * @param command - command to tokenize
 * @param numArgs - pointer to int to store number of arguments
 * @return array of arguments
 */
char **tokenizeCommand(const char *command, int *numArgs);

#endif