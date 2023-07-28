#include "main.h"

char *_getenv(const char *name)
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
