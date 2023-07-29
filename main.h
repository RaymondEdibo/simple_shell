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

#define READ_BUFFSIZE 1024
#define WRITE_BUFFSIZE 1024
#define HI_ST_FILE	".simple_shell_history"
#define HI_ST_MAX	4096
#define BUFF_FLUSH -1
#define CD_NORM	0
#define CONV_LOWERCASE	1
#define CONV_UNSIGNED	2
#define CD_OR		1
#define CD_AND		2
#define CD_CHAIN	3
#define USE_GET_LINE 0
#define USE_STR_TOK 0

extern char **environ;


/**
 * struct list_str - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct list_str
{
	int num;
	char *str;
	struct list_str *next;
} list_t;

/**
 * struct passinfo - contains pseudo-arguements to pass into a function,
 * allowing uniform prototype for function pointer struct
 * @arg: A string generated from getline containing arguments.
 * @argv: An array of strings generated from arg.
 * @path: A string path for the current command.
 * @argc: The argument count.
 * @line_count: The error count.
 * @err_num: The error code for exit() calls.
 * @linecount_flag: If this flag is on, count this line of input.
 * @fname: The program filename.
 * @env: Linked list, a local copy of environ.
 * @environ: A custom modified copy of environ from the linked list env.
 *  @history: The history node.
 * @alias: The alias node.
 * @env_changed: A flag, on if environ was changed.
 * @status: The return status of the last executed command.
 * @cmd_buf: Address of the pointer to cmd_buf, on if chaining.
 * @cmd_buf_type: CD_type or logical operators ||, &&, ;.
 * @readfd: The file descriptor from which to read line input.
 * @histcount: The history line number count.
 */
typedef struct passinfo
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
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_IN_IT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct built_in - contains a built_in string and related function
 * @type: the built_in command flag
 * @func: the function
 */
typedef struct built_in
{
	char *type;
	int (*func)(info_t *);
} built_in_table;


int _is_cmd(info_t *, char *);
char *_dup_char(char *, int, int);
char *_fd_path(info_t *, char *, char *);
int loopmy_shell(char **);
void _my_puts(char *);
int _my_putchar(char);
int my_shell(info_t *, char **);
int _find_built_in(info_t *);
void _find_cmd(info_t *);
void _fork_cmd(info_t *);
int _my_putfd(char c, int fd);
int _my_puts_fd(char *str, int fd);
int my_strlen(char *);
int my_strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *my_strcat(char *, char *);
char *my_strcpy(char *, char *);
char *my_strdup(const char *);
void _puts(char *);
int _putchar(char);
char *_strn_cpy(char *, char *, int);
char *_strn_cat(char *, char *, int);
char *_str_chr(char *, char);
char **str_tow(char *, char *);
char **str_tow2(char *, char);
char *__mem_set(char *, char, unsigned int);
void _f_free(char **);
void *_re_alloc(void *, unsigned int, unsigned int);
int _be_free(void **);
int _error_atoi(char *);
void _print_error(info_t *, char *);
int _print_dec(int, int);
char *conv_number(long int, int, int);
void rmv_comments(char *);
int _my_history(info_t *);
int _my_alias(info_t *);
int interact(info_t *);
int isdelim(char, char *);
int _is_alpha(int);
int _atoi(char *);
ssize_t get_input(info_t *);
int _get_line(info_t *, char **, size_t *);
void _ctrlC(int);
void _clr_info(info_t *);
void _st_info(info_t *, char **);
void _fr_info(info_t *, int);
char *_get_env(info_t *, const char *);
int _my_env(info_t *);
int _my_set_env(info_t *);
int _my_un_set_env(info_t *);
int _populate_env_list(info_t *);
char **_get_envirn(info_t *);
int _un_set_env(info_t *, char *);
int _set_env(info_t *, char *, char *);
char *_get_histry_file(info_t *info);
int _wrt_history(info_t *info);
int _rd_history(info_t *info);
int _bld_history_list(info_t *info, char *buf, int linecount);
int re_number_history(info_t *info);
list_t *_add_node(list_t **, const char *, int);
list_t *_add_node_end(list_t **, const char *, int);
size_t prnt_list_str(const list_t *);
int _rm_node_at_index(list_t **, unsigned int);
void _free_list(list_t **);
size_t _list_length(const list_t *);
char **_list_to_str(list_t *);
size_t _print_list(const list_t *);
int _my_exit(info_t *);
int _my_cd(info_t *);
int _my_help(info_t *);
list_t *_node_starts(list_t *, char *, char);
ssize_t _get_index(list_t *, list_t *);
int chain_delim(info_t *, char *, size_t *);
void _check_chain(info_t *, char *, size_t *, size_t, size_t);
int change_alias(info_t *);
int change_vars(info_t *);
int replace_string(char **, char *);

#endif
