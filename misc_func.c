#include "main.h"

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
	char r_path[PATH_MAX];

	char *p_part = strtok(path_arr_cpy, delim);

	while (p_part)
	{
		char *fp_cmd = p_concat(p_part, cmd);
		if (stat(fp_cmd, &file_exist) == 0)
		{
			t_path = fp_cmd;
			return (t_path);
			break;
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


char *p_concat(char *path, char *command)
{
    char *new_str = malloc(sizeof(char) * (_strlen(path) + _strlen(command) + 1));
    int i = 0, j = 0;
    while (path[i])
    {
        new_str[i] = path[i];
        i++;
    }

    new_str[i] += '/';
    i++;

    while (command[j])
    {
        new_str[i] += command[j];
        i++;
        j++;
    }

    new_str[i] = '\0';

    return (new_str);
}

const char* get_env_value(const char* name) {
     size_t name_len = strlen(name);
	 extern char **environ;
     char** env_ptr = environ;

     while (*env_ptr) {
         if (strncmp(*env_ptr, name, name_len) == 0 && (*env_ptr)[name_len] == '=')
             return *env_ptr + name_len + 1;
         env_ptr++;
     }

     return NULL;
}


int _strlen(char *str)
{
	size_t i = 0;

	for (i = 0; *str; i++)
		str++;

	return (i);
}

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
}
