#include "main.h"

/**
 * _my_exit - exits shell
 * @info: Structure
 *
 * Return: exit status
 */
int _my_exit(info_t *info)
{
	int exitcheck;

	if (info->argv[1]) /* If there is an exit arguement */
	{
		exitcheck = _error_atoi(info->argv[1]);
		if (exitcheck == -1)
		{
			info->status = 2;
			_print_error(info, "Illegal number: ");
			_my_puts(info->argv[1]);
			_my_putchar('\n');
			return (1);
		}
		info->err_num = _error_atoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _my_cd - change current directory
 * @info: Structure
 *
 * Return: Always 0
 */
int _my_cd(info_t *info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = _get_env(info, "HOME=");
		if (!dir)
			chdir_ret = /* TODO: what should this be? */
				chdir((dir = _get_env(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (my_strcmp(info->argv[1], "-") == 0)
	{
		if (!_get_env(info, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_get_env(info, "OLDPWD=")), _putchar('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((dir = _get_env(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		_print_error(info, "can't cd to ");
		_my_puts(info->argv[1]), _my_putchar('\n');
	}
	else
	{
		_set_env(info, "OLDPWD", _get_env(info, "PWD="));
		_set_env(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _my_help - change current directory
 * @info: Structure
 *
 * Return: Always 0
 */
int _my_help(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array); /* temp att_unused workaround */
	return (0);
}
