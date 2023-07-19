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

#define BUFFER 1024

void prompt(void);
ssize_t read_input(char *input, size_t max_l);
void execute(char *c);
int _strlen(char *str);
char *path(char *input);
char *p_concat(char *path, char *command);
char  *s_concat(char *str1, char *str2);
int _strlen(char *str);
char *resolve_r_path(char *input);
const char *get_env_value(const char *name);
char **get_arguments(char *input);


extern char **environ;

#endif
