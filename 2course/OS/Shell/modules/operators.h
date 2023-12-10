#ifndef OPERATOR_H
#define OPERATOR_H

#include "parser.h"
#include "pipes.h"
#include "process.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * Function sets up default pipes for process if they are not already set up
 * Default pipes redirect to console
 */
void defaultPipes(Data *data, bool stdoutRedirect);

/*
 * Function to process(resolve tree) and run command
 * @param root - root of the tree to process
 * @return status of the command
 */
int processAndRun(Node *root);

/*
 * Function to handle && operator
 * @param root - root of the tree to process
 * @param left - pipe to read from
 * @param stdinRedirect - flag to determine if stdin should be redirected
 * @param stdoutRedirect - flag to determine if stdout should be redirected
 * @return status of the command
 */
Data *handleAndOperator(Node *root, int left[2], bool stdinRedirect,
                        bool stdoutRedirect);

/*
 * Function to handle || operator
 * @param root - root of the tree to process
 * @param left - pipe to read from
 * @param stdinRedirect - flag to determine if stdin should be redirected
 * @param stdoutRedirect - flag to determine if stdout should be redirected
 * @return status of the command
 */
Data *handleOrOperator(Node *root, int left[2], bool stdinRedirect,
                       bool stdoutRedirect);

/*
 * Function to handle | operator
 * @param root - root of the tree to process
 * @param left - pipe to read from
 * @param stdinRedirect - flag to determine if stdin should be redirected
 * @param stdoutRedirect - flag to determine if stdout should be redirected
 * @return status of the command
 */
Data *handlePipeOperator(Node *root, int left[2], bool stdinRedirect,
                         bool stdoutRedirect);

/*
 * Function to handle ; operator
 * @param root - root of the tree to process
 * @param left - pipe to read from
 * @param stdinRedirect - flag to determine if stdin should be redirected
 * @param stdoutRedirect - flag to determine if stdout should be redirected
 * @return status of the command
 */
Data *handleListOperator(Node *root, int left[2], bool stdinRedirect,
                         bool stdoutRedirect);

/*
 * Function to handle > operator
 * @param root - root of the tree to process
 * @param left - pipe to read from
 * @param stdinRedirect - flag to determine if stdin should be redirected
 * @return status of the command
 */
Data *handleWriteOperator(Node *root, int left[2], bool stdinRedirect);

/*
 * Function to handle >> operator
 * @param root - root of the tree to process
 * @param left - pipe to read from
 * @param stdinRedirect - flag to determine if stdin should be redirected
 * @return status of the command
 */
Data *handleAppendOperator(Node *root, int left[2], bool stdinRedirect);

/*
 * Function to handle < operator
 * @param root - root of the tree to process
 * @param left - pipe to read from
 * @param stdoutRedirect - flag to determine if stdout should be redirected
 * @return status of the command
 */
Data *handleReadOperator(Node *root, int left[2], bool stdoutRedirect);

/*
 * Function to handle & operator
 * @param root - root of the tree to process
 * @param left - pipe to read from
 * @return status of the command
 */
Data *handleDaemonOperator(Node *root, int left[2]);

/*
 * Function to handle subshell ()
 * @param root - root of the tree to process
 * @param left - pipe to read from
 * @param stdinRedirect - flag to determine if stdin should be redirected
 * @param stdoutRedirect - flag to determine if stdout should be redirected
 * @return status of the command
 */
Data *subshellize(Node *root, int left[2], bool stdinRedirect,
                  bool stdoutRedirect);

/*
 * Function to resolve tree
 * @param root - root of the tree to process
 * @param left - pipe to read from
 * @param stdinRedirect - flag to determine if stdin should be redirected
 * @param stdoutRedirect - flag to determine if stdout should be redirected
 * @return status of the command
 */
Data *resolve(Node *root, int left[2], bool stdinRedirect, bool stdoutRedirect);

#endif