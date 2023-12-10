#ifndef PROCESS_H
#define PROCESS_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

typedef struct Data {
  // Arguments for execution
  char *command;
  int inPipe[2];
  pid_t inPipePid;
  int outPipe[2];
  pid_t outPipePid;
  int errPipe[2];
  pid_t errPipePid;
  bool daemon;

  // Result of execution
  pid_t pid;
  int status;
} Data;

extern Data *activeProgram;
Data *prepareExecData(char *command);
void freeExecData(Data *data);
void handleSignal(int signal);
void startSignalsPassthrough(Data *data);
void stopSignalsPassthrough();
void execute(Data *data);
void waitProcess(Data *data);

#endif