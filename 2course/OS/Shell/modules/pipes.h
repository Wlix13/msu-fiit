#ifndef PIPES_H
#define PIPES_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#define CHUNK 4

pid_t pipeToFD(int fd[2], int d);
pid_t pipeToFile(int fd[2], char *file, int append);
pid_t pipeFromFile(int fd[2], char *file);
pid_t pipeFromTo(int fd1[2], int fd2[2]);

#endif