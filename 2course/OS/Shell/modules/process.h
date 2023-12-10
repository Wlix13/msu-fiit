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

/*
 * Function to create a new Data struct(prepare for execution)
 * @param command command to execute
 * @return Data struct
 */
Data *prepareExecData(char *command);

/*
 * Function to free Data struct
 * @param data - Data struct to free
 */
void freeExecData(Data *data);

/*
 * Function to handle signals
 * @param signal - signal to handle
 */
void handleSignal(int signal);

/*
 * Function to start signals passthrough(redirect signals to activeProgram)
 * @param data - Data struct to pass signals to
 */
void startSignalsPassthrough(Data *data);

/*
 * Function to stop signals passthrough(redirect signals to default handlers)
 */
void stopSignalsPassthrough();

/*
 * Function to execute command
 * @param data - Data struct with command to execute
 */
void execute(Data *data);

/*
 * Function to wait for process to end
 * @param data - Data struct with process to wait for
 */
void waitProcess(Data *data);

#endif