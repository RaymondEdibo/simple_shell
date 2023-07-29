#include "main.h"

/**
 * _get_envirn - string array copy of environ
 * @info: Structure
 *
 * Return: 0
 */
char **_get_envirn(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = _list_to_str(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _un_set_env - Remove environment variable
 * @info: Structure
 * @var: string env var
 *
 *  Return: 1 or 0
 */
int _un_set_env(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			info->env_changed = _rm_node_at_index(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->env_changed);
}

/**
 * _set_env - Initialize new environment variable
 * @info: Structure
 * @var: string env var
 * @value: string env var
 *
 *  Return: 0
 */
int _set_env(info_t *info, char *var, char *value)
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
	node = info->env;
	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	_add_node_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}
