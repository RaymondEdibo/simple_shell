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
	size_t name_len = strlen(name);
	char **env_ptr = environ;

	while (*env_ptr)
	{
		if (strncmp(*env_ptr, name, name_len) == 0 && (*env_ptr)[name_len] == '=')
			return (*env_ptr + name_len + 1);
		env_ptr++;
	}

	return (NULL);
}

/**
 * _strlen -  A function to get the length of the strings
 * @str: The string whose length is to be returned
 * Return: The number of characters in the string
*/

int _strlen(char *str)
{
	size_t i = 0;

	for (i = 0; *str; i++)
		str++;

	return (i);
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
		new_str[i] += str2[j];
		i++;
		j++;
	}

	new_str[i] = '\0';

	return (new_str);
	free(new_str);
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
