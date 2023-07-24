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
