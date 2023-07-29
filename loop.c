#include "main.h"

/**
 * my_shell - my main shell loop
 * @info: parameter
 * @av: argument vector from main
 *
 * Return: 0 or 1
 */
int my_shell(info_t *info, char **av)
{
	ssize_t r = 0;
	int built_in_ret = 0;

	while (r != -1 && built_in_ret != -2)
	{
		_clr_info(info);
		if (interact(info))
			_puts("$ ");
		_my_putchar(BUFF_FLUSH);
		r = get_input(info);
		if (r != -1)
		{
			_st_info(info, av);
			built_in_ret = _find_built_in(info);
			if (built_in_ret == -1)
				_find_cmd(info);
		}
		else if (interact(info))
			_putchar('\n');
		_fr_info(info, 0);
	}
	_wrt_history(info);
	_fr_info(info, 1);
	if (!interact(info) && info->status)
		exit(info->status);
	if (built_in_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (built_in_ret);
}

/**
 * _find_built_in - built_in command
 * @info: parameter
 *
 * Return: -1, 0, 1, or 2
 */
int _find_built_in(info_t *info)
{
	int i, built_in_ret = -1;
	built_in_table built_intbl[] = {
		{"exit", _my_exit},
		{"env", _my_env},
		{"help", _my_help},
		{"history", _my_history},
		{"setenv", _my_set_env},
		{"unsetenv", _my_un_set_env},
		{"cd", _my_cd},
		{"alias", _my_alias},
		{NULL, NULL}
	};

	for (i = 0; built_intbl[i].type; i++)
		if (my_strcmp(info->argv[0], built_intbl[i].type) == 0)
		{
			info->line_count++;
			built_in_ret = built_intbl[i].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * _find_cmd - command in PATH
 * @info: parameter
 *
 * Return: void
 */
void _find_cmd(info_t *info)
{
	char *path = NULL;
	int i, k;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, k = 0; info->arg[i]; i++)
		if (!isdelim(info->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = _fd_path(info, _get_env(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		_fork_cmd(info);
	}
	else
	{
		if ((interact(info) || _get_env(info, "PATH=")
					|| info->argv[0][0] == '/') && _is_cmd(info, info->argv[0]))
			_fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			_print_error(info, "not found\n");
		}
	}
}

/**
 * _fork_cmd - forks an exec
 * @info: parameter
 *
 * Return: void
 */
void _fork_cmd(info_t *info)
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
		if (execve(info->path, info->argv, _get_envirn(info)) == -1)
		{
			_fr_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				_print_error(info, "Permission denied\n");
		}
	}
}
