#include "main.h"

/**
 * command_identifier - identifies command to execute
 *
 * @c: getline input 1st position
 *
 * Return: k or error
 **/
char *command_identifier(char *c)
{
	DIR *folder;
	struct dirent *entry;
	char *a, j, **str  = malloc(sizeof(char) * 1024);
	char **k = malloc(sizeof(char) * 1024);
	int i;

	while (*environ != NULL)
	{
		if (!(_strcomp(*environ, "PATH")))
		{
			*str = *environ;
			for (i = 0; i < 9; i++, k++, str++)
			{
				*k = strtok(*str, ":='PATH'");
				folder = opendir(*k);
				if (folder == NULL)
				{
					perror("Unable to read directory");
				}
				while ((entry = readdir(folder)))
				{
					a = entry->d_name;
					j = _strcomp(a, c);
					if (j == 0)
					{
						return (*k);
					}
					if (a == NULL)
					{
						perror("Error");
					}}}}
		environ++;
	}
	return ("Error: Not Found");
}
