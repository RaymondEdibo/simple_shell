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
		char *t_cmd = path(c);
		char **args = get_arguments(c);

		if (pid < 0)
		{
			perror("fork");
			_exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			execve(t_cmd, args, environ);
			perror(c);
			_exit(EXIT_FAILURE);
		}
		else
		{
				wait(NULL);
		}
}

