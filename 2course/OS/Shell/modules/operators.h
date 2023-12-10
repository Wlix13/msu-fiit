#ifndef OPERATOR_H
#define OPERATOR_H

#include "parser.h"
#include "pipes.h"
#include "process.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void defaultPipes(Data *data, bool stdoutRedirect);
int processAndRun(Node *root);
Data *resolve(Node *root, int left[2], bool stdinRedirect, bool stdoutRedirect);
Data *handleAndOperator(Node *root, int left[2], bool stdinRedirect,
                        bool stdoutRedirect);
Data *handleOrOperator(Node *root, int left[2], bool stdinRedirect,
                       bool stdoutRedirect);
Data *handlePipeOperator(Node *root, int left[2], bool stdinRedirect,
                         bool stdoutRedirect);
Data *handleListOperator(Node *root, int left[2], bool stdinRedirect,
                         bool stdoutRedirect);
Data *handleWriteOperator(Node *root, int left[2], bool stdinRedirect);
Data *handleAppendOperator(Node *root, int left[2], bool stdinRedirect);
Data *handleReadOperator(Node *root, int left[2], bool stdoutRedirect);
Data *handleDaemonOperator(Node *root, int left[2]);

#endif