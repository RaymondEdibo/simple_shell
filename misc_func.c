#include "main.h"

/**
 * path - A function that gets the path to a command
 * @input: The input that is gotten from stdin
 * Return: The absolute path to the command
*/

char *path(char *input)
{
	char *cmd = strdup(input);
	char *t_path = malloc(sizeof(char) * PATH_MAX);
	char *f_path = strtok(cmd, " ");
	struct stat file_exist;
	char *bin_path[] = {"/usr/bin/", "/bin/"};
	size_t i = 0;

	if (!cmd || !t_path)
	{
		free(cmd), free(t_path);
		return (NULL);
	}

	for (i = 0; i < 2; i++)
		if (stat(s_concat(bin_path[i], f_path), &file_exist) == 0)
			return (s_concat(bin_path[i], f_path));

	t_path = r_path(cmd);
	return (t_path);
}

/**
 * resolve_r_path - Gets relative path and converts it into
 * absolute path
 * @input: The command given by user
 * Return: The absolute path of the command
*/

char *resolve_r_path(char *input)
{
	char *input_cpy = strdup(input);
	char *fr_path = malloc(sizeof(char) * PATH_MAX);
	const char *home_arr = get_env_value("HOME");
	char *home_arr_cpy = strdup(home_arr);

	if (!input_cpy || !fr_path || !home_arr_cpy)
	{
		free(input_cpy);
		free(fr_path);
		free(home_arr_cpy);
		return (NULL);
	}
	if (input[0] == '/')
	{
		free(home_arr_cpy);
		return (input_cpy);
	}
	if (input_cpy[0] == '~')
	{
		char *r_path = s_concat(home_arr_cpy, input_cpy + 1);

		if (r_path)
		{
			_strncpy(fr_path, r_path, PATH_MAX - 1);
			free(r_path);
		}
		else
		{
			free(input_cpy);
			free(fr_path);
			free(home_arr_cpy);
			return (NULL);
	}
	}
	else
		realpath(input, fr_path);

	free(input_cpy);
	free(home_arr_cpy);
	return (fr_path);
}


/**
 * get_arguments - A function that gets cli args
 * @input: The input given to the cli
 * Return: An array of arguments
*/

char **get_arguments(char *input)
{
	char **args = malloc(sizeof(char *) * MAX_INPUT);
	char delim[] = " ";
	char *p_args = strtok(input, delim);
	size_t i = 0, j = 0, l = 0;
	char bash_variables[] = {'.', '/', '~'};

	if (!args)
		return (NULL);

	while (p_args)
	{
		j = _strlen(p_args);
		args[i] = malloc(sizeof(char) * PATH_MAX);
		if (!args[i])
		{
			free(args);
			return (NULL);
		}
		for (l = 0; bash_variables[l]; l++)
		{
			if (p_args[0] == bash_variables[l])
			{
				p_args = resolve_r_path(p_args);
				j = _strlen(p_args);
				break;
			}
		}
		strncpy(args[i], p_args, j);
		args[i][j] = '\0';
		p_args = strtok(NULL, delim);
		i++;
	}
	args[i] = NULL;

	free(p_args);

	return (args);
}
