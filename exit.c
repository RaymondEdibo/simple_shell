#include "main.h"

/**
 **_strn_cpy - copies string
 *@dest: the destination
 *@src: the source
 *@n: the amount of characters
 *
 *Return: concatenated string
 */
char *_strn_cpy(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 **_strn_cat - concatenates strings
 *@dest: destination
 *@src: source
 *@n: the amount of bytes
 *
 *Return: concatenated string
 */
char *_strn_cat(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (j < n)
		dest[i] = '\0';
	return (s);
}

/**
 **_str_chr - locates a char in a string
 *@s: string to be parsed
 *@c: character to find
 *Return: pointer to the memory
 */
char *_str_chr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
