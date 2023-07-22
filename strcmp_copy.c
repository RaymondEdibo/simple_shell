#include "main.h"
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
            return 0;
        i++;
        j++;
    }
    return (*i == *j);
}
