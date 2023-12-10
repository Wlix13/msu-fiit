#ifndef PIPES_H
#define PIPES_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#define CHUNK 4

/*
 * Function to make output of process go to file descriptor
 * @param fd - pipe to redirect
 * @param d - file descriptor to redirect to
 */
pid_t pipeToFD(int fd[2], int d);

/*
 * Function to make output of process go to file
 * @param fd - pipe to redirect
 * @param file - file to redirect to
 * @param append - flag to determine if file should be appended
 */
pid_t pipeToFile(int fd[2], char *file, int append);

/*
 * Function to make input of process go from file
 * @param fd - pipe to redirect
 * @param file - file to redirect from
 */
pid_t pipeFromFile(int fd[2], char *file);

/*
 * Function to make input of process go from pipe and output go to pipe
 * @param fd1 - pipe to redirect from
 * @param fd2 - pipe to redirect to
 */
pid_t pipeFromTo(int fd1[2], int fd2[2]);

#endif