#include "main.h"

/**
 * chain_delim - test if a chain delimeter
 * @info: struct
 * @buf: char buffer
 * @p: current position in buf
 *
 * Return: 1 or 0
 */
int chain_delim(info_t *info, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CD_AND;
	}
	else if (buf[j] == ';') /* found end of this command */
	{
		buf[j] = 0; /* replace semicolon with null */
		info->cmd_buf_type = CD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * _check_chain - checks chaining
 * @info: struct
 * @buf: char buffer
 * @p: current position in buf
 * @i: starting position in buf
 * @len: length of buf
 *
 * Return: Void
 */
void _check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (info->cmd_buf_type == CD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (info->cmd_buf_type == CD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
 * change_alias - replaces an aliases
 * @info: struct
 *
 * Return: 1 or 0
 */
int change_alias(info_t *info)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = _node_starts(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _str_chr(node->str, '=');
		if (!p)
			return (0);
		p = my_strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * change_vars - replaces vars
 * @info: struct
 *
 * Return: 1 or 0
 */
int change_vars(info_t *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!my_strcmp(info->argv[i], "$?"))
		{
			replace_string(&(info->argv[i]),
					my_strdup(conv_number(info->status, 10, 0)));
			continue;
		}
		if (!my_strcmp(info->argv[i], "$$"))
		{
			replace_string(&(info->argv[i]),
					my_strdup(conv_number(getpid(), 10, 0)));
			continue;
		}
		node = _node_starts(info->env, &info->argv[i][1], '=');
		if (node)
		{
			replace_string(&(info->argv[i]),
					my_strdup(_str_chr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[i], my_strdup(""));

	}
	return (0);
}

/**
 * replace_string - replaces string
 * @old: old string
 * @new: new string
 *
 * Return: 1 or 0
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
