#include "main.h"

/**
 * findslash - finds slash.
 * @a: 1st string
 *
 * Return: 1 else 0.
 */
int findslash(char *a)
{
	int i = 0;

	while (a[i])
	{
		if (a[0] == '/')
		{
			printf("%c\n", a[0]);
			return (1);
		}

		i++;
	}
	return (0);
}

/**
 * checkexit - exit
 * @a: first
 * @b: exit
 *
 * Return: 1 else 0.
 */
int checkexit(char *a, char *b)
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
 * envcheck - env
 * @a: first
 * @b: exit
 * Return: 1 else 0.
 */
int envcheck(char *a, char *b)
{
	int i = 0;

	for (; (*b != '\0' && *a != '\0') && *a == *b; a++)
	{
		if (i == 2)
			break;
		i++;
		b++;
	}

	return (*a - *b);
}
/**
 * check_string - check input
 * @s: prompt
 * Return: str
 **/
char **check_string(char *s)
{
	char **buffer = malloc(1024 * sizeof(char *));
	char *a;
	int i = 0;
	char *d = " \t\n";


	a = strtok(s, d);

	while (a != NULL)
	{
		buffer[i] = a;
		i++;
		a = strtok(NULL, d);
	}
	execute_shell(buffer);
	return (buffer);

}
/**
 * ctrlC - avoid close the shell
 * @s: keep going shell
 **/
void  ctrlC(int s)
{
	(void) s;
	write(1, "\n$ ", 3);
}
