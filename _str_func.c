#include "main.h"

/**
 * _atoi - Convert string to integer
 * @a: The string to convert
 * Return: The integer value, or -1 if invalid input
 */
int _atoi(char *a)
{
	int integer = 0;

	while (*a)
	{
		if (*a < '0' || *a > '9')
			return (-1);
		integer = integer * 10 + (*a - '0');
		a++;
	}
	return (integer);
}

/**
 * _strcpy - A function that copies strings from
 * src string to dest string
 * @dest: The destination of the copying
 * @src: The source of the string to be copied
 * Return: The copied string (dest)
 */

char *_strcpy(char *dest, const char *src)
{
	char *dest_start = dest;

	while (*src != '\0')
		*dest++ = *src++;

	*dest = '\0';

	return (dest_start);
}

/**
 * _strncpy - A function that copies strings from
 * src to dest and has a limit
 * @dest: The destination of the copied string
 * @src: The destination of the source string
 * @n: The number of characters to be copied
 * Return: The copied string (dest)
 */

char *_strncpy(char *dest, const char *src, size_t n)
{
	char *dest_start = dest;

	while (*src != '\0' && n > 1)
	{
		*dest++ = *src++;
		n--;
	}

	while (n > 0)
	{
		*dest++ = '\0';
		n--;
	}

	return (dest_start);
}

/**
 * _strlen -  A function to get the length of the strings
 * @str: The string whose length is to be returned
 * Return: The number of characters in the string
*/

int _strlen(char *str)
{
	size_t i = 0;

	for (i = 0; *str; i++)
		str++;

	return (i);
}

/**
 * _c_strlen - A replica of strlen but for consts
 * @str: The string to be counted
 * Return: The number of characters in a string
*/

int _c_strlen(const char *str)
{
	size_t i = 0;

	for (i = 0; *str; i++)
		str++;

	return (i);
}
