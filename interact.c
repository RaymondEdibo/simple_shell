#include "main.h"

/**
 * interact - is interact mode
 * @srt: address
 *
 * Return: 1 or 0
 */
int interact(info_t *srt)
{
	return (isatty(STDIN_FILENO) && srt->readfd <= 2);
}

/**
 * isdelim - char is a delimeter
 * @c: the char 
 * @delim: delimeter
 *
 * Return: 1 or 0
 */
int isdelim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 * _is_alpha - checks alphabet
 * @d: The char
 *
 * Return: 1 or  0
 */

int _is_alpha(int d)
{
	if ((d >= 'a' && d <= 'z') || (d >= 'A' && d <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - string to integer
 * @s: the string
 *
 * Return: 0 or converted
 */

int _atoi(char *s)
{
	int i, k = 1, b = 0, answer;
	unsigned int res = 0;

	for (i = 0; s[i] != '\0' && b != 2; i++)
	{
		if (s[i] == '-')
			k *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			b = 1;
			res *= 10;
			res += (s[i] - '0');
		}
		else if (b == 1)
			b = 2;
	}

	if (k == -1)
		answer = -res;
	else
		answer = res;

	return (answer);
}
