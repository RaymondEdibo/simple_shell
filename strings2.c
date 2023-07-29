#include "main.h"

/**
 * my_strcpy - copies string
 * @dest: destination
 * @src: source
 *
 * Return: destination
 */
char *my_strcpy(char *dest, char *src)
{
	int i = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

/**
 * my_strdup - duplicates string
 * @str: the string
 *
 * Return: duplicated string
 */
char *my_strdup(const char *str)
{
	int length = 0;
	char *ret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	for (length++; length--;)
		ret[length] = *--str;
	return (ret);
}

/**
 * _puts - input string
 * @str: the string
 *
 * Return: none
 */
void _puts(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_putchar(str[i]);
		i++;
	}
}

/**
 * _putchar - writes char to stdout
 * @c: char
 *
 * Return: 1 or -1
 */
int _putchar(char c)
{
	static int i;
	static char buf[WRITE_BUFFSIZE];

	if (c == BUFF_FLUSH || i >= WRITE_BUFFSIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (c != BUFF_FLUSH)
		buf[i++] = c;
	return (1);
}
