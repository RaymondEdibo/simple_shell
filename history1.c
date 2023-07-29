#include "main.h"

/**
 * _get_histry_file - history file
 * @info: struct
 *
 * Return: allocated string with history file
 */

char *_get_histry_file(info_t *info)
{
	char *buf, *dir;

	dir = _get_env(info, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (my_strlen(dir) + my_strlen(HI_ST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	my_strcpy(buf, dir);
	my_strcat(buf, "/");
	my_strcat(buf, HI_ST_FILE);
	return (buf);
}

/**
 * _wrt_history - creates or appends file
 * @info: struct
 *
 * Return: 1 or -1
 */
int _wrt_history(info_t *info)
{
	ssize_t fd;
	char *filename = _get_histry_file(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_my_puts_fd(node->str, fd);
		_my_putfd('\n', fd);
	}
	_my_putfd(BUFF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * _rd_history - reads history
 * @info: struct
 *
 * Return: histcount or 0
 */
int _rd_history(info_t *info)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = _get_histry_file(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			_bld_history_list(info, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		_bld_history_list(info, buf + last, linecount++);
	free(buf);
	info->histcount = linecount;
	while (info->histcount-- >= HI_ST_MAX)
		_rm_node_at_index(&(info->history), 0);
	re_number_history(info);
	return (info->histcount);
}

/**
 * _bld_history_list - adds entry
 * @info: Structure
 * @buf: buffer
 * @linecount: histcount
 *
 * Return: Always 0
 */
int _bld_history_list(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	_add_node_end(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * re_number_history - renumbers history linked list
 * @info: Structure
 * Return: new histcount
 */
int re_number_history(info_t *info)
{
	list_t *node = info->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (info->histcount = i);
}
