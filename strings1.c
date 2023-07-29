#include "main.h"

/**
 * my_strlen - length of a string
 * @s: the string
 *
 * Return: length
 */
int my_strlen(char *s)
{
	int i = 0;

	if (!s)
		return (0);

	while (*s++)
		i++;
	return (i);
}

/**
 * my_strcmp - comparison of two strings.
 * @s1: first string
 * @s2: second string
 *
 * Return: -1, 1 or 0
 */
int my_strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * starts_with - if needle starts with haystack
 * @haystack: to search
 * @needle: substring to find
 *
 * Return: address of next char
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * my_strcat - concatenates strings
 * @dest: destination
 * @src: source
 *
 * Return: pointer to destination buffer
 */
char *my_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}
