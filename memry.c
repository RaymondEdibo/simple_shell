#include "main.h"

/**
 * _be_free - frees pointer
 * @ptr: address to be free
 *
 * Return: 1 or  0.
 */
int _be_free(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
