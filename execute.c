#include "main.h"
/**
 * execute_shell - executes shell commands
 * @a: a pointer
 *
 * Return: 
 */
void execute_shell(char **a)
{

	char *i = (*(a + 1));
	char *j, *slash_sign = "/";
	char *k;
	char *f = *a;
	char *argv[4];

	if ((access(a[0], F_OK) == 0))
	{
		argv[0] = a[0];
		argv[1] = i;
		argv[2] = ".";
		argv[3] = NULL;

		if (execve(argv[0], argv, NULL) == -1)
		{
			perror("Error");
		}
	}
	else
	{
		k = command_identifier(f);

		slash_sign = str_concat(k, slash_sign);

		j = str_concat(slash_sign, *a);

		argv[0] = j;
		argv[1] = i;
		argv[2] = ".";
		argv[3] = NULL;

		if (execve(argv[0], argv, NULL) == -1)
		{
			perror("Error");
		}
	}
}
