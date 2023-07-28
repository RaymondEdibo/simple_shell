#include "main.h"

/**
 * inputbuf - buffers chained commands
 * @a: parameter struct
 * @buf: address of buffer
 * @len: address of len var
 *
 * Return: bytes read
 */
ssize_t inputbuf(info_t *a, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len) /* if nothing left in the buffer, fill it */
	{
		/*b_free((void **)a->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigin_t_Handler);
#if USEGETLINE
		r = get_line(buf, &len_p, stdin);
#else
		r = _get_line(a, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0'; /* remove trailing newline */
				r--;
			}
			a->linecount_flag = 1;
			rm_comments(*buf);
			buildhistorylist(a, *buf, a->histcount++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*len = r;
				a->cmd_buf = buf;
			}
		}
	}
	return (r);
}

/**
 * getinput - gets a line minus the newline
 * @a: parameter struct
 *
 * Return: bytes read
 */
ssize_t getinput(info_t *a)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(a->arg), *p;

	my_putchar(BUFF_FLUSH);
	r = inputbuf(a, &buf, &len);
	if (r == -1) /* EOF */
		return (-1);
	if (len) /* we have commands left in the chain buffer */
	{
		j = i; /* init new iterator to current buf position */
		p = buf + i; /* get pointer for return */

		checkchain(a, buf, &j, i, len);
		while (j < len) /* iterate to semicolon or end */
		{
			if (ischain(a, buf, &j))
				break;
			j++;
		}

		i = j + 1; /* increment past nulled ';'' */
		if (i >= len) /* reached end of buffer? */
		{
			i = len = 0; /* reset position and length */
			a->cmd_buf_type = CMDNORM;
		}

		*buf_p = p; /* pass back pointer to current command position */
		return (my_strlen(p)); /* return length of current command */
	}

	*buf_p = buf; /* else not a chain, pass back buffer from _get_line() */
	return (r); /* return length of buffer from _get_line() */
}

/**
 * readbuf - reads a buffer
 * @a: parameter struct
 * @buf: buffer
 * @i: size
 *
 * Return: r
 */
ssize_t readbuf(info_t *a, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(a->readfd, buf, READ_BUFF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * _get_line - gets the next line of input from STDIN
 * @a: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int _get_line(info_t *a, char **ptr, size_t *length)
{
	static char buf[READ_BUFF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = readbuf(a, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = my_realloc(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + i, k - i);
	else
		my_strncpy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigin_t_Handler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void sigin_t_Handler(__attribute__((unused))int sig_num)
{
	my_puts("\n");
	my_puts("$ ");
	my_putchar(BUFF_FLUSH);
}

