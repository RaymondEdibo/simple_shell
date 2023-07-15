#include "main.h"
/**
 * execute - Execute command
 * @c: the command
 *
 * Return: void
 */
void execute(char *c)
{
		pid_t pid = fork();
		char *args[2];

		if (pid < 0)
		{
				perror("fork");
				_exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
				args[0] = c;
				args[1] = NULL;
				execve(c, args, NULL);
				perror("execve");
				_exit(EXIT_FAILURE);
		}
		else
		{
				wait(NULL);
		}
}

