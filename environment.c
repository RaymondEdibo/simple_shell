#include "main.h"

/**
 * _my_env - prints current environment
 * @info: Structure
 *
 * Return: Always 0
 */
int _my_env(info_t *info)
{
	prnt_list_str(info->env);
	return (0);
}

/**
 * _get_env - value of environ variable
 * @info: Structure
 * @name: env var name
 *
 * Return: the value
 */
char *_get_env(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * _my_set_env -new environment variable
 * @info: Structure
 *
 *  Return: 0
 */
int _my_set_env(info_t *info)
{
	if (info->argc != 3)
	{
		_my_puts("Incorrect number of arguements\n");
		return (1);
	}
	if (_set_env(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _my_un_set_env - Remove environment variable
 * @info: Structure
 *
 * Return: Always 0
 */
int _my_un_set_env(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_my_puts("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		_un_set_env(info, info->argv[i]);

	return (0);
}

/**
 * _populate_env_list - populates env LL
 * @info: Structure
 *
 * Return: Always 0
 */
int _populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		_add_node_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}
