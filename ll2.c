#include "main.h"

/**
 * _list_length - length of linked list
 * @h: first node
 *
 * Return: listsize
 */
size_t _list_length(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * _list_to_str - returns an array of strings of the list->str
 * @head: first node
 *
 * Return: strings of array
 */
char **_list_to_str(list_t *head)
{
	list_t *node = head;
	size_t i = _list_length(head), j;
	char **strs;
	char *str;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(my_strlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = my_strcpy(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}


/**
 * _print_list - elements of a list_t linked list
 * @h: first node
 *
 * Return: listsize
 */
size_t _print_list(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(conv_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * _node_starts - returns node whose string starts with prefix
 * @node: list head
 * @prefix: string to match
 * @c: next character after prefix
 *
 * Return: match node
 */
list_t *_node_starts(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = starts_with(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * _get_index - ndex of a node
 * @head: list head
 * @node: node
 *
 * Return: index of node or -1
 */
ssize_t _get_index(list_t *head, list_t *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}
