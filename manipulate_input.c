#include "main.h"

/**
 * get_arguments - Get the arguments
 * @input: The arguments given
 * Return: An array of strings
*/

char **get_arguments(char *input)
{
	char **arguments = (char **)malloc((ARGS_MAX + 1) * sizeof(char *));
	char *token;
	int arg_index;

	if (!arguments)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	arg_index = 0;

	token = strtok(input, " \t\n");

	while (token != NULL && arg_index < ARGS_MAX)
	{
		arguments[arg_index] = token;
		token = strtok(NULL, " \t\n");
		arg_index++;
	}

	arguments[arg_index] = NULL;

	return (arguments);
}

/**
 * free_arguments - Free arguments
 * @arguments: The input given
*/

void free_arguments(char **arguments)
{
	int i = 0;

	while (arguments[i] != NULL)
	{
		free(arguments[i]);
		i++;
	}
	free(arguments);
}

/**
 * file_exists - Check if file exists
 * @input: The input to be given
 * Return: 1 on success, 0 on failure
*/

short int file_exists(char *input)
{
	struct stat file_present;

	if (stat(input, &file_present) == 0)
		return (1);

	return (0);
}
