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
	size_t i = 0;

	char *p_part = strtok(path_arr_cpy, delim);

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

	while (bash_variables[i])
	{
		if (bash_variables[i] == tf_cmd[0])
		{
			t_path = resolve_r_path(cmd);
		}

		i++;
	}

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
		return (fr_path);
	}

	if (input_cpy[0] == '~')
	{
		input_cpy++;
		fr_path = s_concat(home_arr_cpy, input_cpy);
		return (fr_path);
	}

	realpath(input, fr_path);

	return (fr_path);
}
