#include "main.h"

/**
 * main - entry point
 * @ac: arg count
 * @av: arg vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int ac, char **av)
{
	info_t a[] = { INFO_INIT };
	int fd = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (fd)
			: "r" (fd));

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_emy_puts(av[0]);
				_emy_puts(": 0: Can't open ");
				_emy_puts(av[1]);
				_emy_putchar('\n');
				_emy_putchar(BUFF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		a->readfd = fd;
	}
	populate_envlist(a);
	readhistory(a);
	hsh(a, av);
	return (EXIT_SUCCESS);
}

