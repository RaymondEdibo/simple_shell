#include "main.h"

/**
 * This _execvp function is for a dry run one,
 * It is not meant to be used forever,
 * like a temporary fix
*/

int _strlen(char *str);
char  *_strcat(char *str1, char *str2);
void _execvp(char *input)
{
    char d[] = ":";
    char *sys_path = getenv("PATH");
    char *args[2];
    pid_t pid;

    char *p_part = strtok(sys_path, d);

    while (p_part != NULL)
    {
        char *e_command = _strcat(p_part, input);
        pid = execve(e_command, args,NULL);
        p_part = strtok(NULL, d);
    }

}

char  *_strcat(char *str1, char *str2)
{
    char *new_str = malloc(sizeof(char) * (_strlen(str1) + _strlen(str2) + 1));
    int i = 0, j = 0;
    while (str1[i])
    {
        new_str[i] = str1[i];
        i++;
    }

    new_str[i] += '/';
    i++;

    while (str2[j])
    {
        new_str[i] += str2[j];
        i++;
        j++;
    }

    new_str[i] = '\0';

    return (new_str);
}

int _strlen(char *str)
{
    int i = 0;

    for (i = 0; *str; i++)
        str++;

    return (i);
}