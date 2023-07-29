#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

#define READ_BUFF_SIZE 1024
#define WRITE_BUFF_SIZE 1024
#define BUFF_FLUSH -1

#define CMDNORM	0
#define CMDOR		1
#define CMDAND		2
#define CMDCHAIN	3

#define CONV_LOWERCASE	1
#define CONV_UNSIGNED	2

#define USEGETLINE 0
#define USESTRTOK 0

#define HISTFILE	".simple_shell_history"
#define HISTMAX	4096

extern char **env;


/**
 * struct mylist - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct mylist
{
	int num;
	char *str;
	struct mylist *next;
} list_t;

/**
 * struct passa - contains pseudo-arguements to pass into a function,
 * allowing uniform prototype for function pointer struct
 * @arg: a string generated from get_line containing arguements
 * @argv:an array of strings generated from arg
 * @path: a string path for the current command
 * @argc: the argument count
 * @line_count: the error count
 * @err_num: the error code for exit()s
 * @linecount_flag: if on count this line of input
 * @fname: the program filename
 * @env: linked list local copy of env
 * @env: custom modified copy of env from LL env
 * @history: the history node
 * @alias: the alias node
 * @env_changed: on if env was changed
 * @status: the return status of the last exec'd command
 * @cmd_buf: address of pointer to cmd_buf, on if chaining
 * @cmd_buf_type: CMDtype ||, &&, ;
 * @readfd: the fd from which to read line input
 * @histcount: history number count
 */
typedef struct passa
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **_env;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMDtype ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct builtin - contains a builtin string and related function
 * @type: the builtin command flag
 * @func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


int hsh(info_t *, char **);
int find_builtin(info_t *);
void findcmd(info_t *);
void forkcmd(info_t *);
int iscmd(info_t *, char *);
char *char_duplicates(char *, int, int);
char *pathfind(info_t *, char *, char *);
int loophsh(char **);
void _emy_puts(char *);
int _emy_putchar(char);
int _put_fd(char c, int fd);
int my_puts_fd(char *str, int fd);
int my_strlen(char *);
int my_strcmp(char *, char *);
char *begins_with(const char *, const char *);
char *my_strcat(char *, char *);
char *my_strcpy(char *, char *);
char *my_strdup(const char *);
void my_puts(char *);
int my_putchar(char);
char *my_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);
char **str_tow(char *, char *);
char **str_tow_2(char *, char);
char *my_memset(char *, char, unsigned int);
void ffree(char **);
void *my_realloc(void *, unsigned int, unsigned int);
int b_free(void **);
int interact(info_t *);
int delim_check(char, char *);
int _is_alphabet(int);
int _atoi(char *);
int _err_atoi(char *);
void printerror(info_t *, char *);
int printd(int, int);
char *conv_number(long int, int, int);
void rm_comments(char *);
int _my_exit(info_t *);
int _my_cd(info_t *);
int _my_help(info_t *);
int _my_history(info_t *);
int _my_alias(info_t *);
ssize_t getinput(info_t *);
int _get_line(info_t *, char **, size_t *);
void sigin_t_Handler(int);
void cleara(info_t *);
void seta(info_t *, char **);
void freea(info_t *, int);
char *_get_env(info_t *, const char *);
int _my_env(info_t *);
int _my_set_env(info_t *);
int _my_un_set_env(info_t *);
int populate_envlist(info_t *);
char **get_env(info_t *);
int _un_set_env(info_t *, char *);
int _set_env(info_t *, char *, char *);
char *gethistoryfile(info_t *a);
int writehistory(info_t *a);
int readhistory(info_t *a);
int buildhistorylist(info_t *a, char *buf, int linecount);
int renumberhistory(info_t *a);
list_t *addnode(list_t **, const char *, int);
list_t *addnode_end(list_t **, const char *, int);
size_t printlist_string(const list_t *);
int delete_index_node(list_t **, unsigned int);
void freelist(list_t **);
size_t list_length(const list_t *);
char **list_to_str(list_t *);
size_t printlist(const list_t *);
list_t *node_start(list_t *, char *, char);
ssize_t get_nodeindex(list_t *, list_t *);
int ischain(info_t *, char *, size_t *);
void checkchain(info_t *, char *, size_t *, size_t, size_t);
int alias_replace(info_t *);
int vars_replace(info_t *);
int string_replace(char **, char *);

#endif
