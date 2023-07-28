#include "main.h"

/**
 * prompt - the prompt
 *
 **/
void prompt(void)
{
	for (;;)
	{
		char *input = NULL, **environ;
		pid_t child_pid;
		int a, lb;
		size_t buff_size = 0;

		my_puts("$ ");
		lb = getline(&input, &buff_size, stdin);
		if (lb == -1)
			exit(98);
		if (checkexit(input, "exit") == 0)
			exit(0);
		if (envcheck(input, "env") == 0)
		{
			while (*environ != NULL)
			{
				if (!(_strcomp(*environ, "USER")) ||
						!(_strcomp(*environ, "LANGUAGE")) ||
						!(_strcomp(*environ, "SESSION")) ||
						!(_strcomp(*environ, "COMPIZ_CONFIG_PROFILE")) ||
						!(_strcomp(*environ, "SHLV")) ||
						!(_strcomp(*environ, "HOME")) ||
						!(_strcomp(*environ, "C_IS")) ||
						!(_strcomp(*environ, "DESKTOP_SESSION")) ||
						!(_strcomp(*environ, "LOGNAME")) ||
						!(_strcomp(*environ, "TERM")) ||
						!(_strcomp(*environ, "PATH")))
				{
					my_puts(*environ), my_puts("\n"); }
				environ++; }}
		child_pid = fork();
		if (child_pid < 0)
			perror("Error");
		if (child_pid == 0)
			check_string(input);
		else
			wait(&a);
	}}
