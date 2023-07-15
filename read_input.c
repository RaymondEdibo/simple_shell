#include "main.h"
/**
 * read_input - Read stdin input
 * @input: the input
 * @max_l: Maximum input length
 *
 * Return: Number read
 */
ssize_t read_input(char *input, size_t max_l)
{
	ssize_t reader;

	reader = read(STDIN_FILENO, input, max_l);
	if (reader == -1)
	{
		perror("reader");
		_exit(EXIT_FAILURE);
	}
	return (reader);
}
