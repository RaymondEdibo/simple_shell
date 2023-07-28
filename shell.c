#include "main.h"

/**
 * main - The shell
 * @ac: void
 * @av: void
 *
 * Return: 0
 **/
int main(int ac, char **av)
{
	(void)av;
	(void)ac;

	signal(SIGINT, ctrlC);
	prompt();
	return (0);
}
