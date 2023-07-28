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
		pid_t pid;
		int status;
		char **args = get_arguments(c);
		char *cmd = strtok(c, " ");

		if (!file_exists(cmd))
		{
			dprintf(STDERR_FILENO, "%s: %ld: %s: not found\n", p_name, i, c);
			free(args);
			return;
		}

		pid = fork();
		if (!args)
		{
			free(args);
			args = NULL;
		}

		if (pid < 0)
		{
			perror("fork");
			_exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			execve(args[0], args, NULL);
			_exit(EXIT_FAILURE);
		}
		else
			wait(&status);

		free(args);
}

