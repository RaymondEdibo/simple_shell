#include "main.h"

/**
 * _my_history - displays history
 * @info: Structure
 *
 *  Return: Always 0
 */
int _my_history(info_t *info)
{
	_print_list(info->history);
	return (0);
}

/**
 * _un__set_alias - alias to string
 * @info: struct
 * @str: string alias
 *
 * Return: 0 or 1
 */
int _un__set_alias(info_t *info, char *str)
{
	char *p, c;
	int ret;

	p = _str_chr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = _rm_node_at_index(&(info->alias),
		_get_index(info->alias, _node_starts(info->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * _set_alias - alias to string
 * @info: struct
 * @str: string alias
 *
 * Return: 0 or 1
 */
int _set_alias(info_t *info, char *str)
{
	char *p;

	p = _str_chr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (_un__set_alias(info, str));

	_un__set_alias(info, str);
	return (_add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * _print_alias - alias string
 * @node: alias node
 *
 * Return: 0 or 1
 */
int _print_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _str_chr(node->str, '=');
		for (a = node->str; a <= p; a++)
		_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _my_alias - mimics alias
 * @info: Structure
 *
 *  Return: 0
 */
int _my_alias(info_t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			_print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = _str_chr(info->argv[i], '=');
		if (p)
			_set_alias(info, info->argv[i]);
		else
			_print_alias(_node_starts(info->alias, info->argv[i], '='));
	}

	return (0);
}
