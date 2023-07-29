#include "main.h"

/**
 * ischain - test if current char in buffer is a chain delimeter
 * @a: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int ischain(info_t *a, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		a->cmd_buf_type = CMDOR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		a->cmd_buf_type = CMDAND;
	}
	else if (buf[j] == ';') /* found end of this command */
	{
		buf[j] = 0; /* replace semicolon with null */
		a->cmd_buf_type = CMDCHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * checkchain - checks we should continue chaining based on last status
 * @a: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 * @i: starting position in buf
 * @len: length of buf
 *
 * Return: Void
 */
void checkchain(info_t *a, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (a->cmd_buf_type == CMDAND)
	{
		if (a->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (a->cmd_buf_type == CMDOR)
	{
		if (!a->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
 * alias_replace - replaces an aliases in the tokenized string
 * @a: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int alias_replace(info_t *a)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = node_start(a->alias, a->argv[0], '=');
		if (!node)
			return (0);
		free(a->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = my_strdup(p + 1);
		if (!p)
			return (0);
		a->argv[0] = p;
	}
	return (1);
}

/**
 * vars_replace - replaces vars in the tokenized string
 * @a: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int vars_replace(info_t *a)
{
	int i = 0;
	list_t *node;

	for (i = 0; a->argv[i]; i++)
	{
		if (a->argv[i][0] != '$' || !a->argv[i][1])
			continue;

		if (!my_strcmp(a->argv[i], "$?"))
		{
			string_replace(&(a->argv[i]),
					my_strdup(conv_number(a->status, 10, 0)));
			continue;
		}
		if (!my_strcmp(a->argv[i], "$$"))
		{
			string_replace(&(a->argv[i]),
					my_strdup(conv_number(getpid(), 10, 0)));
			continue;
		}
		node = node_start(a->env, &a->argv[i][1], '=');
		if (node)
		{
			string_replace(&(a->argv[i]),
					my_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		string_replace(&a->argv[i], my_strdup(""));

	}
	return (0);
}

/**
 * string_replace - replaces string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int string_replace(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
/**
 * **str_tow - splits a string into words. Repeat delimiters are ignored
 * @str: the input string
 * @d: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **str_tow(char *str, char *d)
{
	int i, j, k, m, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!delim_check(str[i], d) && (delim_check(str[i + 1], d) || !str[i + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (delim_check(str[i], d))
			i++;
		k = 0;
		while (!delim_check(str[i + k], d) && str[i + k])
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}

/**
 * **str_tow_2 - splits a string into words
 * @str: the input string
 * @d: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **str_tow_2(char *str, char d)
{
	int i, j, k, m, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != d && str[i + 1] == d) ||
				    (str[i] != d && !str[i + 1]) || str[i + 1] == d)
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (str[i] == d && str[i] != d)
			i++;
		k = 0;
		while (str[i + k] != d && str[i + k] && str[i + k] != d)
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}

/**
 * my_strcpy - copies a string
 * @dest: the destination
 * @src: the source
 *
 * Return: pointer to destination
 */
char *my_strcpy(char *dest, char *src)
{
	int i = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

/**
 * my_strdup - duplicates a string
 * @str: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *my_strdup(const char *str)
{
	int length = 0;
	char *ret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	for (length++; length--;)
		ret[length] = *--str;
	return (ret);
}

/**
 * my_puts - prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void my_puts(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		my_putchar(str[i]);
		i++;
	}
}

/**
 * my_putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int my_putchar(char c)
{
	static int i;
	static char buf[WRITE_BUFF_SIZE];

	if (c == BUFF_FLUSH || i >= WRITE_BUFF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (c != BUFF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * my_strlen - returns the length of a string
 * @s: the string whose length to check
 *
 * Return: integer length of string
 */
int my_strlen(char *s)
{
	int i = 0;

	if (!s)
		return (0);

	while (*s++)
		i++;
	return (i);
}

/**
 * my_strcmp - performs lexicogarphic comparison of two strangs.
 * @s1: the first strang
 * @s2: the second strang
 *
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */
int my_strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * begins_with - checks if needle starts with haystack
 * @haystack: string to search
 * @needle: the substring to find
 *
 * Return: address of next char of haystack or NULL
 */
char *begins_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * my_strcat - concatenates two strings
 * @dest: the destination buffer
 * @src: the source buffer
 *
 * Return: pointer to destination buffer
 */
char *my_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}

/**
 * interact - checks if in interactive
 * @a: address
 *
 * Return: 1 or 0
 */
int interact(info_t *a)
{
	return (isatty(STDIN_FILENO) && a->readfd <= 2);
}

/**
 * delim_check - checks if is a delimeter
 * @c: the char
 * @i: delimeter
 *
 * Return: 1 if true, 0 if false
 */
int delim_check(char c, char *i)
{
	while (*i)
		if (*i++ == c)
			return (1);
	return (0);
}

/**
 * _is_alphabet - checks alphabet
 *
 * @i: The char
 * Return: 1 or 0 otherwise
 */

int _is_alphabet(int i)
{
	if ((i >= 'a' && i <= 'z') || (i >= 'A' && i <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - string to integer
 *
 * @str: the string
 * Return: 0 or
 */

int _atoi(char *str)
{
	int i, a = 1, b = 0, output;
	unsigned int result = 0;

	for (i = 0; str[i] != '\0' && b != 2; i++)
	{
		if (str[i] == '-')
			a *= -1;

		if (str[i] >= '0' && str[i] <= '9')
		{
			b = 1;
			result *= 10;
			result += (str[i] - '0');
		}
		else if (b == 1)
			b = 2;
	}

	if (a == -1)
		output = -result;
	else
		output = result;

	return (output);
}
