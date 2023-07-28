#include "main.h"
/**
 * main - the Shell
 * @argc: Number
 * @argv: The char array
 * Return: result
 */
int main(UNUSED int argc, char *argv[])
{
	char input[BUFFER];
	ssize_t reader, i = 1;

	while (1)
	{
		short int is_term = isatty(STDIN_FILENO);

		if (is_term)
			prompt();

		reader = read_input(input, MAX_INPUT, is_term);

		if (reader == 0)
			_exit(EXIT_SUCCESS);

		input[reader - 1] = '\0';

		if (reader > 1 && input[0] != '\0')
		{
			execute(input, argv[0], i);
			i++;
		}
	}

	return (EXIT_SUCCESS);
	i++;
}
