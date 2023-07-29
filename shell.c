#include "main.h"

/**
 * main - shell program main
 * @ac: arg count
 * @av: arg vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int ac, char **av)
{
	info_t info[] = { INFO_IN_IT };
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
				_my_puts(av[0]);
				_my_puts(": 0: Can't open ");
				_my_puts(av[1]);
				_my_putchar('\n');
				_my_putchar(BUFF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = fd;
	}
	_populate_env_list(info);
	_rd_history(info);
	my_shell(info, av);
	return (EXIT_SUCCESS);
}
