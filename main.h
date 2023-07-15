#ifndef MAIN_H
#define MAIN_H

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

#define MAX_INPUT 1024

void prompt(void);
ssize_t read_input(char *input, size_t max_l);
void execute(char *c);

#endif
