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
		extern char **environ;
		char *t_cmd = path(c);
		char *args[] = {t_cmd,NULL};
		printf("%s\n", t_cmd);

		if (pid < 0)
		{
				perror("fork");
				_exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
				execve(args[0], args, environ);
				perror(c);
				_exit(EXIT_FAILURE);
		}
		else
		{
				wait(NULL);
		}
}

