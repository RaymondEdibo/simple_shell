#include "main.h"

/**
 * __mem_set - fills memory
 * @s: pointer to memory area
 * @b: byte to fill
 * @n: amount to be filled
 * Return: pointer to memory area
 */
char *__mem_set(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;
	return (s);
}

/**
 * _f_free - free string of strings
 * @pp: a string of strings
 */
void _f_free(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}

/**
 * _re_alloc - reallocates
 * @ptr: previous malloc'ated block
 * @old_size: previous block
 * @new_size: new block
 *
 * Return: pointer to da ol'block nameen.
 */
void *_re_alloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}
