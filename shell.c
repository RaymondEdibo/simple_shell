#include "main.h"
/**
 * main - the Shell
 *
 * Return: result
 */
int main(void)
{
	char input[MAX_INPUT];
	ssize_t reader;

	while (1)
	{
		prompt();
		reader = read_input(input, MAX_INPUT);

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
