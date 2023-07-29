#include "main.h"

/**
 * _my_puts - prints input string
 * @str: the string
 *
 * Return: none
 */
void _my_puts(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_my_putchar(str[i]);
		i++;
	}
}

/**
 * _my_putchar - writes char to stderr
 * @c: The char
 *
 * Return: 1 or -1
 */
int _my_putchar(char c)
{
	static int i;
	static char buf[WRITE_BUFFSIZE];

	if (c == BUFF_FLUSH || i >= WRITE_BUFFSIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != BUFF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * _my_putfd - writes char to fd
 * @c: The char
 * @fd: The filedescriptor
 *
 * Return: 1 or -1
 */
int _my_putfd(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUFFSIZE];

	if (c == BUFF_FLUSH || i >= WRITE_BUFFSIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != BUFF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * _my_puts_fd - prints input string
 * @str: the string
 * @fd: the filedescriptor
 *
 * Return: number of chars put
 */
int _my_puts_fd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += _my_putfd(*str++, fd);
	}
	return (i);
}
