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
	short int is_term = isatty(STDIN_FILENO);

	while (1)
	{
		if(is_term)
			prompt();

		reader = read_input(input, MAX_INPUT);

		if (reader == 0)
		{
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
