#include "main.h"

/**
 * _input_buff - buffers
 * @info: struct
 * @buf: buffer
 * @len: length var
 *
 * Return: bytes
 */
ssize_t _input_buff(info_t *info, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len) /* if nothing left in the buffer, fill it */
	{
		/*_be_free((void **)info->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, _ctrlC);
#if USE_GET_LINE
		r = getline(buf, &len_p, stdin);
#else
		r = _get_line(info, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0'; /* remove trailing newline */
				r--;
			}
			info->linecount_flag = 1;
			rmv_comments(*buf);
			_bld_history_list(info, *buf, info->histcount++);
			/* if (_str_chr(*buf, ';')) is this a command chain? */
			{
				*len = r;
				info->cmd_buf = buf;
			}
		}
	}
	return (r);
}

/**
 * get_input - gets line minus newline
 * @info: struct
 *
 * Return: bytes
 */
ssize_t get_input(info_t *info)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUFF_FLUSH);
	r = _input_buff(info, &buf, &len);
	if (r == -1) /* EOF */
		return (-1);
	if (len) /* we have commands left in the chain buffer */
	{
		j = i; /* init new iterator to current buf position */
		p = buf + i; /* get pointer for return */

		_check_chain(info, buf, &j, i, len);
		while (j < len) /* iterate to semicolon or end */
		{
			if (chain_delim(info, buf, &j))
				break;
			j++;
		}

		i = j + 1; /* increment past nulled ';'' */
		if (i >= len) /* reached end of buffer? */
		{
			i = len = 0; /* reset position and length */
			info->cmd_buf_type = CD_NORM;
		}

		*buf_p = p; /* pass back pointer to current command position */
		return (my_strlen(p)); /* return length of current command */
	}

	*buf_p = buf; /* else not a chain, pass back buffer from _get_line() */
	return (r); /* return length of buffer from _get_line() */
}

/**
 * _read_buff - reads buffer
 * @info: struct
 * @buf: buffer
 * @i: size
 *
 * Return: r
 */
ssize_t _read_buff(info_t *info, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(info->readfd, buf, READ_BUFFSIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * _get_line - gets next line of input
 * @info: struct
 * @ptr: address of pointer to buffer
 * @length: size of preallocated buffer
 *
 * Return: s
 */
int _get_line(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUFFSIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = _read_buff(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _str_chr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _re_alloc(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		_strn_cat(new_p, buf + i, k - i);
	else
		_strn_cpy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * _ctrlC - blocks ctrl-C
 * @sig_num: signal number
 *
 * Return: no
 */
void _ctrlC(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUFF_FLUSH);
}
