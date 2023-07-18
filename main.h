#ifndef MAIN_H
#define MAIN_H

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdio.h>

#define MAX_INPUT 1024
#define MAX_PATH ((MAX_INPUT * MAX_INPUT))


void prompt(void);
ssize_t read_input(char *input, size_t max_l);
void execute(char *c);
int _strlen(char *str);
char *path(char *input);
char *p_concat(char *path, char *command);
int _strlen(char *str);

#endif
