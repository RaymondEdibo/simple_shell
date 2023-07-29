#include "main.h"

/**
 * _getenv - Get the environment variables in the form
 * NAME=VALUE
 * @name: The name of the environment
 * Return: The value(s) of the NAME variable
*/

char *_getenv(const char *name)
{
	size_t name_len;
	char **env_ptr = environ;

	if (name == NULL || name[0] == '\0')
		return (NULL);

	name_len = strlen(name);

	while (*env_ptr)
	{
		if (strncmp(*env_ptr, name, name_len) == 0 && (*env_ptr)[name_len] == '=')
			return (*env_ptr + name_len + 1);
		env_ptr++;
	}

	return (NULL);
}
