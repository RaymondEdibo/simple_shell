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
	short int is_term = isatty(STDIN_FILENO);

	while (1)
	{
		if (is_term)
			prompt();
		reader = read_input(input, BUFFER);

		if (reader == 0)
		{
			write(STDOUT_FILENO, "\n", 1);
			built_in_exit();
		}

		input[reader - 1] = '\0';

		if (reader > 1)
		{
			execute(input);
		}
	}

	return (EXIT_SUCCESS);
}
