#include "main.h"

/**
 * hsh - main shell loop
 * @a: the parameter 
 * @av: the argument 
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(info_t *a, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		cleara(a);
		if (interact(a))
			my_puts("$ ");
		_emy_putchar(BUFF_FLUSH);
		r = getinput(a);
		if (r != -1)
		{
			seta(a, av);
			builtin_ret = find_builtin(a);
			if (builtin_ret == -1)
				findcmd(a);
		}
		else if (interact(a))
			my_putchar('\n');
		freea(a, 0);
	}
	writehistory(a);
	freea(a, 1);
	if (!interact(a) && a->status)
		exit(a->status);
	if (builtin_ret == -2)
	{
		if (a->err_num == -1)
			exit(a->status);
		exit(a->err_num);
	}
	return (builtin_ret);
}

/**
 * find_builtin - finds a builtin command
 * @a: the parameter & return a struct
 *
 * Return: -1 if builtin not found,
 * 	0 if builtin executed successfully,
 * 	1 if builtin found but not successful,
 * 	2 if builtin signals exit()
 */
int find_builtin(info_t *a)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _my_exit},
		{"env", _my_env},
		{"help", _my_help},
		{"history", _my_history},
		{"set_env", _my_set_env},
		{"un_set_env", _my_un_set_env},
		{"cd", _my_cd},
		{"alias", _my_alias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (my_strcmp(a->argv[0], builtintbl[i].type) == 0)
		{
			a->line_count++;
			built_in_ret = builtintbl[i].func(a);
			break;
		}
	return (built_in_ret);
}

/**
 * findcmd - finds a command in PATH
 * @a: the parameter & return a struct
 *
 * Return: void
 */
void findcmd(info_t *a)
{
	char *path = NULL;
	int i, k;

	a->path = a->argv[0];
	if (a->linecount_flag == 1)
	{
		a->line_count++;
		a->linecount_flag = 0;
	}
	for (i = 0, k = 0; a->arg[i]; i++)
		if (!delim_check(a->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = pathfind(a, _get_env(a, "PATH="), a->argv[0]);
	if (path)
	{
		a->path = path;
		forkcmd(a);
	}
	else
	{
		if ((interact(a) || _get_env(a, "PATH=")
					|| a->argv[0][0] == '/') && iscmd(a, a->argv[0]))
			forkcmd(a);
		else if (*(a->arg) != '\n')
		{
			a->status = 127;
			printerror(a, "not found\n");
		}
	}
}

/**
 * forkcmd - forks a an exec thread to run cmd
 * @a: the parameter & return a struct
 *
 * Return: void
 */
void forkcmd(info_t *a)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(a->path, a->argv, get_env(a)) == -1)
		{
			freea(a, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(a->status));
		if (WIFEXITED(a->status))
		{
			a->status = WEXITSTATUS(a->status);
			if (a->status == 126)
				printerror(a, "Permission denied\n");
		}
	}
}

