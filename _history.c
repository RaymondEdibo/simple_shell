#include "main.h"

/**
 * gethistoryfile - gets the history file
 * @a: parameter struct
 *
 * Return: allocated string containg history file
 */

char *gethistoryfile(info_t *a)
{
	char *buf, *dir;

	dir = _get_env(a, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (my_strlen(dir) + my_strlen(HISTFILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	my_strcpy(buf, dir);
	my_strcat(buf, "/");
	my_strcat(buf, HISTFILE);
	return (buf);
}

/**
 * writehistory - creates a file, or appends to an existing file
 * @a: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int writehistory(info_t *a)
{
	ssize_t fd;
	char *filename = gethistoryfile(a);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = a->history; node; node = node->next)
	{
		my_puts_fd(node->str, fd);
		_put_fd('\n', fd);
	}
	_put_fd(BUFF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * readhistory - reads history from file
 * @a: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int readhistory(info_t *a)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = gethistoryfile(a);

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
			buildhistorylist(a, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		buildhistorylist(a, buf + last, linecount++);
	free(buf);
	a->histcount = linecount;
	while (a->histcount-- >= HISTMAX)
		delete_index_node(&(a->history), 0);
	renumberhistory(a);
	return (a->histcount);
}

/**
 * buildhistorylist - adds entry to a history linked list
 * @a: Structure
 * @buf: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0
 */
int buildhistorylist(info_t *a, char *buf, int linecount)
{
	list_t *node = NULL;

	if (a->history)
		node = a->history;
	addnode_end(&node, buf, linecount);

	if (!a->history)
		a->history = node;
	return (0);
}

/**
 * renumberhistory - renumbers the history linked list after changes
 * @a: Structure
 *
 * Return: the new histcount
 */
int renumberhistory(info_t *a)
{
	list_t *node = a->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (a->histcount = i);
}
/**
 * b_free - frees a pointer and NULLs the address
 * @ptr: address of the pointer to free
 *
 * Return: 1 if freed, otherwise 0.
 */
int b_free(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}

