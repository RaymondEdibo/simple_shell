#include "main.h"
/**
 * execute - Execute command
 * @c: the command
 * @p_name: Program name
 * @i: Execution number
 *
 * Return: void
 */
void execute(char *c, char *p_name, size_t i)
{
		pid_t pid = fork();
		char *args[2];
		int status;

		if (pid < 0)
		{
			perror("fork");
			_exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			args[0] = c;
			args[1] = NULL;
			if (execve(c, args, NULL))
			dprintf(STDERR_FILENO, "%s: %ld: %s: not found", p_name, i, c);
			_exit(EXIT_FAILURE);
		}
		else
		{
			wait(&status);
		}
}
