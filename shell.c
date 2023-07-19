#include "main.h"
/**
 * main - the Shell
 *
 * Return: result
 */
int main(void)
{
	char input[BUFFER];
	ssize_t reader;

	while (1)
	{
		prompt();
		reader = read_input(input, BUFFER);

		if (reader == 0)
		{
			write(STDOUT_FILENO, "\n", 1);
			_exit(EXIT_SUCCESS);
		}

		input[reader - 1] = '\0';

		if (reader > 1)
		{
			execute(input);
		}
	}

	return (EXIT_SUCCESS);
}
