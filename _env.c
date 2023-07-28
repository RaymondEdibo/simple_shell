#include "main.h"

/**
 * _my_env - prints the current envment
 * @a: Structure
 * Return: 0
 */
int _my_env(info_t *a)
{
	printlist_string(a->env);
	return (0);
}

/**
 * _get_env - gets the value of an env variable
 * @a: Structure
 * @name: env var name
 *
 * Return: the value
 */
char *_get_env(info_t *a, const char *name)
{
	list_t *node = a->env;
	char *p;

	while (node)
	{
		p = begins_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * _my_set_env - Initialize a new envment variable,
 *             or modify an existing one
 * @a: Structure
 *        constant function prototype.
 *  Return: Always 0
 */
int _my_set_env(info_t *a)
{
	if (a->argc != 3)
	{
		_emy_puts("Incorrect number of arguements\n");
		return (1);
	}
	if (_set_env(a, a->argv[1], a->argv[2]))
		return (0);
	return (1);
}

/**
 * _my_un_set_env - Remove an envment variable
 * @a: Structure
 *        constant function prototype.
 * Return: Always 0
 */
int _my_un_set_env(info_t *a)
{
	int i;

	if (a->argc == 1)
	{
		_emy_puts("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= a->argc; i++)
		_un_set_env(a, a->argv[i]);

	return (0);
}

/**
 * populate_envlist - populates env linked list
 * @a: Structure
 *          constant function prototype.
 * Return: Always 0
 */
int populate_envlist(info_t *a)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; env[i]; i++)
		addnode_end(&node, env[i], 0);
	a->env = node;
	return (0);
}
/**
 * get_env - returns the string array copy of our env
 * @a: Structure
 *          constant function prototype.
 * Return: Always 0
 */
char **get_env(info_t *a)
{
	if (!a->env || a->env_changed)
	{
		a->env = list_to_str(a->env);
		a->env_changed = 0;
	}

	return (a->env);
}

/**
 * _un_set_env - Remove an envment variable
 * @a: Structure
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @var: the string env var property
 */
int _un_set_env(info_t *a, char *var)
{
	list_t *node = a->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = begins_with(node->str, var);
		if (p && *p == '=')
		{
			a->env_changed = delete_index_node(&(a->env), i);
			i = 0;
			node = a->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (a->env_changed);
}

/**
 * _set_env - Initialize a new envment variable,
 *             or modify an existing one
 * @a: Structure
 *        constant function prototype.
 * @var: the string env var property
 * @value: the string env var value
 *  Return: Always 0
 */
int _set_env(info_t *a, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(my_strlen(var) + my_strlen(value) + 2);
	if (!buf)
		return (1);
	my_strcpy(buf, var);
	my_strcat(buf, "=");
	my_strcat(buf, value);
	node = a->env;
	while (node)
	{
		p = begins_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			a->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	addnode_end(&(a->env), buf, 0);
	free(buf);
	a->env_changed = 1;
	return (0);
}
/**
 * cleara - initializes info_t struct
 * @a: struct address
 */
void cleara(info_t *a)
{
	a->arg = NULL;
	a->argv = NULL;
	a->path = NULL;
	a->argc = 0;
}

/**
 * seta - initializes info_t struct
 * @a: struct address
 * @av: argument vector
 */
void seta(info_t *a, char **av)
{
	int i = 0;

	a->fname = av[0];
	if (a->arg)
	{
		a->argv = str_tow(a->arg, " \t");
		if (!a->argv)
		{
			a->argv = malloc(sizeof(char *) * 2);
			if (a->argv)
			{
				a->argv[0] = my_strdup(a->arg);
				a->argv[1] = NULL;
			}
		}
		for (i = 0; a->argv && a->argv[i]; i++)
			;
		a->argc = i;

		alias_replace(a);
		vars_replace(a);
	}
}

/**
 * freea - frees info_t struct fields
 * @a: struct address
 * @all: true if freeing all fields
 */
void freea(info_t *a, int all)
{
	ffree(a->argv);
	a->argv = NULL;
	a->path = NULL;
	if (all)
	{
		if (!a->cmd_buf)
			free(a->arg);
		if (a->env)
			freelist(&(a->env));
		if (a->history)
			freelist(&(a->history));
		if (a->alias)
			freelist(&(a->alias));
		ffree(a->env);
			a->env = NULL;
		b_free((void **)a->cmd_buf);
		if (a->readfd > 2)
			close(a->readfd);
		my_putchar(BUFF_FLUSH);
	}
}

