#include "main.h"
/**
 * read_input - Read stdin input
 * @input: the input
 * @max_l: Maximum input length
 * @_f: If terminal or not
 *
 * Return: Number read
 */
ssize_t read_input(char *input, size_t max_l, short int _f)
{
	ssize_t reader;


	if (_f)
		reader = read(STDIN_FILENO, input, max_l);
	else
		reader = getline(&input, &max_l, stdin);

	input[reader - 1] = '\0';

	if (reader == -1)
	{
		perror("getline");
		_exit(EXIT_FAILURE);
	}

	return (reader);
}
