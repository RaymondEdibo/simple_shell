#include "main.h"

/**
 * _clr_info - info_t struct
 * @info: struct
 */
void _clr_info(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * _st_info - info_t struct
 * @info: struct
 * @av: argument vector
 */
void _st_info(info_t *info, char **av)
{
	int i = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = str_tow(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = my_strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		change_alias(info);
		change_vars(info);
	}
}

/**
 * _fr_info - frees info_t
 * @info: struct
 * @all: true if freeing all
 */
void _fr_info(info_t *info, int all)
{
	_f_free(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			_free_list(&(info->env));
		if (info->history)
			_free_list(&(info->history));
		if (info->alias)
			_free_list(&(info->alias));
		_f_free(info->environ);
			info->environ = NULL;
		_be_free((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUFF_FLUSH);
	}
}
