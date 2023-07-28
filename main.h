#ifndef _MAIN_H_
#define _MAIN_H_
#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <dirent.h>
#include <limits.h>
#include <string.h>

extern char **environ;

void prompt(void);
int _strlen(char *str);
void my_puts(char *str);
char *command_identifier(char *c);
int _strcomp(char *a, char *b);
int charwrite(char c);
void my_puts(char *str);
char *str_concat(char *a, char *b);
int findslash(char *a);
int checkexit(char *a, char *b);
int envcheck(char *a, char *b);
void execute_shell(char **a);
char **check_string(char *s);
void ctrlC(int s);
#endif
