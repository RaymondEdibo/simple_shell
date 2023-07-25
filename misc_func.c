#include "main.h"

/**
 * path - A function that gets the path to a command
 * @input: The input that is gotten from stdin
 * Return: The absolute path to the command
*/

char *path(char *input)
{
	char *cmd = strdup(input);
	char *tf_cmd = strtok(cmd, " ");
	char *t_path = malloc(sizeof(char) * PATH_MAX);
	char delim[] = ":";
	const char *path_arr = get_env_value("PATH");
	char *path_arr_cpy = strdup(path_arr);
	struct stat file_exist;
	char bash_variables[] = {'.', '/', '~'};
	char bin_path[][PATH_MAX] = {"/usr/bin/", "/bin/"};
	size_t i = 0;
	char *p_part = strtok(path_arr_cpy, delim);

	for (i = 0; bin_path[i]; i++)
		if (stat(s_concat(bin_path[i], cmd), &file_exist) == 0)
			return (s_concat(bin_path[i], cmd));

	t_path = cmd;
	while (p_part)
	{
		char *fp_cmd = p_concat(p_part, cmd);

		if (stat(fp_cmd, &file_exist) == 0)
		{
			t_path = fp_cmd;
			return (t_path);
		}

		p_part = strtok(NULL, delim);
	}

	for (i = 0; bash_variables[i]; i++)
	{
		if (bash_variables[i] == tf_cmd[0])
		{
			free(t_path);
			t_path = resolve_r_path(cmd);
			free(cmd);
			return (t_path);
		}
	}

	free(cmd);
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

	if (input[0] == '/')
	{
		fr_path = input_cpy;
		free(home_arr_cpy);
		free(input_cpy);
		return (fr_path);
	}

	if (input_cpy[0] == '~')
	{
		input_cpy++;
		fr_path = s_concat(home_arr_cpy, input_cpy);
		free(input_cpy);
		free(home_arr_cpy);
		return (fr_path);
	}

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
	size_t k;

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

	return (args);

	for (k = 0; k < i; k++)
	{
		free(args[k]);
	}
	free(args);
}
