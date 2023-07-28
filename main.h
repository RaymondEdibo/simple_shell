#ifndef MAIN_H
#define MAIN_H

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdio.h>
#include <limits.h>
#include <linux/limits.h>
#include <errno.h>

#define BUFFER 1024
#define UNUSED __attribute__((unused))

void prompt(void);
ssize_t read_input(char *input, size_t max_l, short int _f);
void execute(char *c, char *p_name, size_t i);

extern char **environ;

#endif
