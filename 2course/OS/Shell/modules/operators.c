#include "operators.h"
#include "utils.h"

void defaultPipes(Data *data, bool stdoutRedirect) {
  if (!data->outPipePid && stdoutRedirect)
    data->outPipePid = pipeToFD(data->outPipe, STDOUT_FILENO);
  if (!data->errPipePid)
    data->errPipePid = pipeToFD(data->errPipe, STDERR_FILENO);
}

int processAndRun(Node *root) {
  Data *data = resolve(root, (int[2]){STDIN_FILENO, STDOUT_FILENO}, true, true);

  if (data->status == -1)
    waitProcess(data);

  int status = data->status;

  closeIrrelevantFDs((int[]){STDIN_FILENO, STDOUT_FILENO, STDERR_FILENO, -1});

  freeExecData(data);

  return status;
}

Data *handleAndOperator(Node *root, int left[2], bool stdinRedirect,
                        bool stdoutRedirect) {
  Data *s1 = resolve(root->left, left, stdinRedirect, stdoutRedirect);
  waitProcess(s1);

  if (s1->status == 0) {
    freeExecData(s1);
    // Handle success of first process
    return resolve(root->right, left, stdinRedirect, stdoutRedirect);
  } else {
    // Handle failure of first process
    return s1;
  }
}

Data *handleOrOperator(Node *root, int left[2], bool stdinRedirect,
                       bool stdoutRedirect) {
  Data *r = resolve(root->left, left, stdinRedirect, stdoutRedirect);
  waitProcess(r);

  if (r->status > 0) {
    // Handle failure of first process
    freeExecData(r);
    return resolve(root->right, left, stdinRedirect, stdoutRedirect);
  }

  return r;
}

Data *handlePipeOperator(Node *root, int left[2], bool stdinRedirect,
                         bool stdoutRedirect) {
  Data *r1 = resolve(root->left, left, stdinRedirect, false);

  if (DEBUG)
    printf("DEBUG: Command %s PID - %d finished R/W/E(%d, %d, %d)\n",
           r1->command, r1->pid, r1->inPipePid, r1->outPipePid, r1->errPipePid);

  Data *r2 = resolve(root->right, r1->outPipe, true, stdoutRedirect);

  waitProcess(r1);
  freeExecData(r1);

  return r2;
}

Data *handleListOperator(Node *root, int left[2], bool stdinRedirect,
                         bool stdoutRedirect) {
  Data *r = resolve(root->left, left, stdinRedirect, stdoutRedirect);
  waitProcess(r);
  freeExecData(r);

  return resolve(root->right, left, stdinRedirect, stdoutRedirect);
};

Data *handleWriteOperator(Node *root, int left[2], bool stdinRedirect) {
  root->left->isDaemon = root->isDaemon;
  Data *r1 = resolve(root->left, left, stdinRedirect, false);

  r1->outPipePid = pipeToFile(r1->outPipe, root->right->value, false);

  return r1;
};

Data *handleAppendOperator(Node *root, int left[2], bool stdinRedirect) {
  root->left->isDaemon = root->isDaemon;
  Data *r1 = resolve(root->left, left, stdinRedirect, false);

  r1->outPipePid = pipeToFile(r1->outPipe, root->right->value, true);

  return r1;
};

Data *handleReadOperator(Node *root, int left[2], bool stdoutRedirect) {
  root->left->isDaemon = root->isDaemon;
  Data *r1 = resolve(root->left, left, false, stdoutRedirect);

  r1->inPipePid = pipeFromFile(r1->inPipe, root->right->value);

  if (!root->isDaemon) {
    int status;
    waitpid(r1->inPipePid, &status, 0);

    if (WEXITSTATUS(status) != 0) {
      kill(r1->pid, SIGINT);
      r1->status = WEXITSTATUS(status);
      return r1;
    }
  }

  if (left[0] != -1 && left[0] != STDIN_FILENO)
    r1->inPipePid = pipeFromTo(left, r1->inPipe);

  return r1;
};

Data *handleDaemonOperator(Node *root, int left[2]) {
  root->left->isDaemon = 1;
  Data *r1 = resolve(root->left, left, false, true);
  close(r1->inPipe[WRITE_END]);

  printf("[N] %d\n", r1->pid);

  return r1;
};

Data *subshellize(Node *root, int left[2], bool stdinRedirect,
                  bool stdoutRedirect) {
  Data *data = prepareExecData("subshell");
  data->daemon = root->isDaemon;

  if (stdinRedirect)
    data->inPipePid = pipeFromTo(left, data->inPipe);

  if (stdoutRedirect)
    defaultPipes(data, stdoutRedirect);

  pid_t pid;
  if ((pid = fork()) == 0) {
    if (DEBUG)
      printf("DEBUG: Subshell started:\n");

    if (data->daemon)
      setpgrp();

    dup2(data->inPipe[READ_END], STDIN_FILENO);
    dup2(data->outPipe[WRITE_END], STDOUT_FILENO);
    dup2(data->errPipe[WRITE_END], STDERR_FILENO);

    closeIrrelevantFDs((int[]){STDIN_FILENO, STDOUT_FILENO, STDERR_FILENO, -1});

    root->subshell = 0;
    int status = processAndRun(root);

    exit(status);
  }

  data->pid = pid;

  close(data->inPipe[READ_END]);
  close(data->outPipe[WRITE_END]);
  close(data->errPipe[WRITE_END]);

  if (!data->daemon)
    startSignalsPassthrough(data);

  return data;
}

Data *resolve(Node *root, int left[2], bool stdinRedirect,
              bool stdoutRedirect) {
  if (root->subshell)
    return subshellize(root, left, stdinRedirect, stdoutRedirect);

  if (root->isOperator) {
    // Handle operators
    if (!strcmp(root->value, "&&"))
      return handleAndOperator(root, left, stdinRedirect, stdoutRedirect);
    if (!strcmp(root->value, "||"))
      return handleOrOperator(root, left, stdinRedirect, stdoutRedirect);
    if (!strcmp(root->value, "|"))
      return handlePipeOperator(root, left, stdinRedirect, stdoutRedirect);
    if (!strcmp(root->value, ";"))
      return handleListOperator(root, left, stdinRedirect, stdoutRedirect);
    if (!strcmp(root->value, ">"))
      return handleWriteOperator(root, left, stdinRedirect);
    if (!strcmp(root->value, ">>"))
      return handleAppendOperator(root, left, stdinRedirect);
    if (!strcmp(root->value, "<"))
      return handleReadOperator(root, left, stdoutRedirect);
    if (!strcmp(root->value, "&"))
      return handleDaemonOperator(root, left);

    return NULL;
  } else {
    Data *data = prepareExecData(root->value);
    data->daemon = root->isDaemon;

    // Set up pipes
    if (stdinRedirect)
      data->inPipePid = pipeFromTo(left, data->inPipe);
    if (stdoutRedirect)
      defaultPipes(data, stdoutRedirect);

    if (DEBUG)
      printf("DEBUG: Command %s PID - %d is starting R/W/E(%d(%d), %d, %d)\n",
             data->command, data->pid, data->inPipePid, data->inPipe[WRITE_END],
             data->outPipePid, data->errPipePid);

    // Run command
    execute(data);

    // Way to work with cd
    if (strncmp(root->value, "cd", 2) == 0) {
      char *path = root->value + 2;
      int path_length = strlen(path);

      // Trim path
      while (isspace((unsigned char)*path))
        path++;
      while (path_length > 0 && isspace((unsigned char)path[path_length - 1]))
        path_length--;
      path[path_length] = '\0';

      chdir(path);
    }

    if (DEBUG)
      printf("DEBUG: Command %s PID - %d: R/W/E(%d(%d), %d(%d), %d(%d))\n",
             data->command, data->pid, data->inPipePid, data->inPipe[WRITE_END],
             data->outPipePid, data->outPipe[READ_END], data->errPipePid,
             data->errPipe[READ_END]);

    return data;
  }
}
