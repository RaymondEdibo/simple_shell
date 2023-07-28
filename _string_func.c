#include "main.h"

/**
 * p_concat - A function tha concatenates strings and adds
 * a "/" between them
 * @path: The first string or the path that is programmatically
 * generated
 * @command: The second string or the command entered
 *
 * Return: The path
*/

char *p_concat(char *path, char *command)
{
	char *new_str = malloc(sizeof(char) * (_strlen(path) + _strlen(command) + 2));
	int i = 0, j = 0;

	while (path[i])
	{
		new_str[i] = path[i];
		i++;
	}

	new_str[i] = '/';
	i++;

	while (command[j])
	{
		new_str[i] = command[j];
		i++;
		j++;
	}

	new_str[i] = '\0';

	return (new_str);

	free(new_str);
}

/**
 * get_env_value - A function that gets environment values
 * @name: The name of variable in which the value is to be
 * gotten from. More at man environ
 * Return: The environment values
*/

const char *get_env_value(const char *name)
{
	size_t name_len;
	char **env_ptr = environ;

	if (name == NULL || name[0] == '\0')
		return (NULL);

	name_len = _c_strlen(name);

	while (*env_ptr)
	{
		if (strncmp(*env_ptr, name, name_len) == 0 && (*env_ptr)[name_len] == '=')
			return (*env_ptr + name_len + 1);
		env_ptr++;
	}

	return (NULL);
}

/**
 * s_concat - Same as p_concat but doesn't append "/"
 * @str1: The first string
 * @str2: The second string
 *
 * Return: The new concatenated string
*/

char  *s_concat(char *str1, char *str2)
{
	char *new_str = malloc(sizeof(char) * (_strlen(str1) + _strlen(str2) + 1));
	int i = 0, j = 0;

	while (str1[i])
	{
		new_str[i] = str1[i];
		i++;
	}

	while (str2[j])
	{
		new_str[i] = str2[j];
		i++;
		j++;
	}

	new_str[i] = '\0';

	return (new_str);
}

/**
 * _strcmp - Compare two strings
 * @i: first string
 * @j: second string
 * Return: 1 if equal, 0 otherwise
 */
int _strcmp(const char *i, const char *j)
{
	while (*i && *j)
	{
		if (*i != *j)
			return (0);
		i++;
		j++;
	}
	return (*i == *j);
}

/**
 * r_path - Get the path of the first token
 * @input: The whole input token
 * Return: The absolute path of the executable
*/

char *r_path(char *input)
{
	char *t_path = malloc(sizeof(char) * PATH_MAX);
	const char *path_arr = get_env_value("PATH");
	char *path_arr_cpy = strdup(path_arr);
	char bash_variables[] = {'.', '/', '~'};
	char *cmd = strtok(input, " ");
	struct stat file_exist;
	size_t i = 0;
	char delim[] = ":", *p_part = strtok(path_arr_cpy, delim);

	if (!t_path || !p_part || !path_arr_cpy || !cmd)
	{
		free(t_path), free(p_part), free(path_arr_cpy), free(cmd);
		return (NULL);
	}
	while (p_part)
	{
		char *fp_cmd = p_concat(p_part, cmd);

		if (stat(fp_cmd, &file_exist) == 0)
		{
			free(t_path);
			t_path = fp_cmd;
			free(t_path);
		}

		free(fp_cmd);
		p_part = strtok(NULL, delim);
	}
	for (i = 0; bash_variables[i]; i++)
	{
		if (bash_variables[i] == cmd[0])
		{
			free(t_path);
			t_path = resolve_r_path(cmd);
		}
	}

	free(p_part);

	return (t_path);
}
