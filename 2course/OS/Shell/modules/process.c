#include "process.h"
#include "utils.h"

Data *activeProgram = NULL;

Data *prepareExecData(char *command) {
  Data *data = malloc(sizeof(Data));
  data->command = command;
  pipe(data->inPipe);
  pipe(data->outPipe);
  pipe(data->errPipe);
  if (data->errPipe[WRITE_END] > maxFD)
    maxFD = data->errPipe[WRITE_END];

  data->daemon = false;
  data->status = -1;

  return data;
}

void freeExecData(Data *data) {
  if (data == activeProgram)
    activeProgram = NULL;
  free(data);
}

void handleSignal(int sig) {
  if (activeProgram != NULL) {
    if (DEBUG)
      printf("DEBUG: New signal %d\n", sig);
    kill(activeProgram->pid, sig);
    if (activeProgram->inPipePid) {
      kill(activeProgram->inPipePid, sig);
      close(activeProgram->inPipe[WRITE_END]);
    }
  } else
    exit(EXIT_SUCCESS);
}

void startSignalsPassthrough(Data *data) {
  activeProgram = data;
  signal(SIGINT, handleSignal);
  signal(SIGTSTP, handleSignal);
}

void stopSignalsPassthrough() {
  signal(SIGINT, SIG_DFL);
  signal(SIGTSTP, SIG_DFL);
}

void execute(Data *data) {
  char **args = tokenizeCommand(data->command, 0);

  if (DEBUG)
    printf("DEBUG: Running %s (Read: %d(%d), Write: %d(%d), Errors: %d(%d))\n",
           data->command, data->inPipe[WRITE_END], data->inPipe[READ_END],
           data->outPipe[READ_END], data->outPipe[WRITE_END],
           data->errPipe[READ_END], data->errPipe[WRITE_END]);

  pid_t pid;
  if ((pid = fork()) == 0) {
    stopSignalsPassthrough();

    if (data->daemon)
      setpgrp();

    dup2(data->inPipe[READ_END], STDIN_FILENO);
    dup2(data->outPipe[WRITE_END], STDOUT_FILENO);
    dup2(data->errPipe[WRITE_END], STDERR_FILENO);

    closeIrrelevantFDs((int[]){STDIN_FILENO, STDOUT_FILENO, STDERR_FILENO, -1});

    execvp(args[0], args);

    perror("shell");
    exit(127);
  }

  // Free args after fork
  for (int i = 0; args[i] != NULL; i++)
    free(args[i]);

  data->pid = pid;

  close(data->inPipe[READ_END]);
  close(data->outPipe[WRITE_END]);
  close(data->errPipe[WRITE_END]);

  if (!data->daemon)
    startSignalsPassthrough(data);
}

void waitProcess(Data *data) {
  close(data->inPipe[WRITE_END]);
  close(data->outPipe[READ_END]);
  close(data->errPipe[READ_END]);

  if (!data->daemon) {
    if (DEBUG)
      printf("DEBUG: Waiting for%scommand: %s with PID: %d, R/W(%d, %d)\n",
             data->daemon ? "demon " : " ", data->command, data->pid,
             data->inPipePid, data->outPipePid);

    int status;
    waitpid(data->pid, &status, 0);

    if (data->status == -1)
      data->status = WEXITSTATUS(status);

    if (DEBUG)
      printf("Command ended\n");

    if (data->inPipePid) {
      kill(data->inPipePid, SIGINT);
      waitpid(data->inPipePid, NULL, 0);
    }
    if (data->outPipePid)
      waitpid(data->outPipePid, NULL, 0);
    if (data->errPipePid)
      waitpid(data->errPipePid, NULL, 0);

    if (DEBUG)
      printf("DEBUG: Wait done for %s with PID %d R/W(%d, %d)\n", data->command,
             data->pid, data->inPipePid, data->outPipePid);
  } else
    data->status = 0;

  if (data->errPipe[WRITE_END] == maxFD)
    maxFD--;
  if (data->errPipe[READ_END] == maxFD)
    maxFD--;
  if (data->outPipe[WRITE_END] == maxFD)
    maxFD--;
  if (data->outPipe[READ_END] == maxFD)
    maxFD--;
  if (data->inPipe[WRITE_END] == maxFD)
    maxFD--;
  if (data->inPipe[READ_END] == maxFD)
    maxFD--;
}
