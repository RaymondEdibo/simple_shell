#include "main.h"

/**
 * _my_exit - exits the shell
 * @a: Structure
 *
 * Return: exits with a given exit status
 */
int _my_exit(info_t *a)
{
	int exitcheck;

	if (a->argv[1]) /* If there is an exit arguement */
	{
		exitcheck = _err_atoi(a->argv[1]);
		if (exitcheck == -1)
		{
			a->status = 2;
			printerror(a, "Illegal number: ");
			_emy_puts(a->argv[1]);
			_emy_putchar('\n');
			return (1);
		}
		a->err_num = _err_atoi(a->argv[1]);
		return (-2);
	}
	a->err_num = -1;
	return (-2);
}

/**
 * _my_cd - changes the current directory
 * @a: Structure
 *
 * Return: 0
 */
int _my_cd(info_t *a)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		my_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!a->argv[1])
	{
		dir = _get_env(a, "HOME=");
		if (!dir)
			chdir_ret = /* TODO: what should this be? */
				chdir((dir = _get_env(a, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (my_strcmp(a->argv[1], "-") == 0)
	{
		if (!_get_env(a, "OLDPWD="))
		{
			my_puts(s);
			my_putchar('\n');
			return (1);
		}
		my_puts(_get_env(a, "OLDPWD=")), my_putchar('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((dir = _get_env(a, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(a->argv[1]);
	if (chdir_ret == -1)
	{
		printerror(a, "can't cd to ");
		_emy_puts(a->argv[1]), _emy_putchar('\n');
	}
	else
	{
		_set_env(a, "OLDPWD", _get_env(a, "PWD="));
		_set_env(a, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _my_help - changes the current directory
 * @a: Structure
 *
 * Return: 0
 */
int _my_help(info_t *a)
{
	char **arg_array;

	arg_array = a->argv;
	my_puts("help call works. Function not yet implemented \n");
	if (0)
		my_puts(*arg_array); /* temp att_unused workaround */
	return (0);
}
/**
 * _my_history - displays the history list
 * @a: Structure
 *
 *  Return: 0
 */
int _my_history(info_t *a)
{
	printlist(a->history);
	return (0);
}

/**
 * resetalias - sets alias to string
 * @a: struct
 * @str:  string alias
 *
 * Return: 0 on success, 1 on error
 */
int resetalias(info_t *a, char *str)
{
	char *p, c;
	int ret;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delete_index_node(&(a->alias),
		get_nodeindex(a->alias, node_start(a->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * setalias - sets alias to string
 * @a: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int setalias(info_t *a, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (resetalias(a, str));

	resetalias(a, str);
	return (addnode_end(&(a->alias), str, 0) == NULL);
}

/**
 * printalias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int printalias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
		my_putchar(*a);
		my_putchar('\'');
		my_puts(p + 1);
		my_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _my_alias - mimics the alias builtin (man alias)
 * @a: Structure.
 *  Return: Always 0
 */
int _my_alias(info_t *a)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (a->argc == 1)
	{
		node = a->alias;
		while (node)
		{
			printalias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; a->argv[i]; i++)
	{
		p = _strchr(a->argv[i], '=');
		if (p)
			setalias(a, a->argv[i]);
		else
			printalias(node_start(a->alias, a->argv[i], '='));
	}

	return (0);
}

