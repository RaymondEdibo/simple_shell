#include "main.h"

/**
 * _strlen - string length
 * @str: the string.
 *
 * Return: i.
 */
int _strlen(char *str)
{
	int i;

	for (i = 0; str[i] != '\0'; i++)
		;

	return (i);
}

/**
 * str_concat - concatane strings.
 * @a: string.
 * @b: second string.
 *
 * Return: a
 */
char *str_concat(char *a, char *b)
{
	char *let;
	int n, m, j, i, e;

	if (a == NULL)
		a = "";

	if (b == NULL)
		b = "";

	n = _strlen(a);

	m = _strlen(b);

	let = malloc(((n) + (m) + 1) * sizeof(char));

	if (let == NULL)
		return (NULL);

	for (j = 0; j < n; j++)
	{
		let[j] = a[j];
	}

	for (i = n, e = 0; e <= m; i++, e++)
	{
		let[i] = b[e];
	}
	return (let);
}

/**
 * _strcomp - compares strings
 *
 * @a: string 1.
 * @b: string 2.
 *
 * Return: a-b dir
 **/
int _strcomp(char *a, char *b)
{
	int i = 0;

	for (; (*b != '\0' && *a != '\0') && *a == *b; a++)
	{
		if (i == 3)
			break;
		i++;
		b++;
	}

	return (*a - *b);
}

/**
 * charwrite - writes character
 * @c: The character
 *
 * Return: 1 or -1
 */
int charwrite(char c)
{
	return (write(1, &c, 1));
}

/**
 * my_puts - puts copy
 * @str: string
 *
 * Return: 0
 */
void my_puts(char *str)
{
	while (*str != '\0')
	{
		charwrite(*str);
		str++;
	}
}
