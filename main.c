#include "main.h"

/**
 * main - functionthat calls the other functions. it is the parent function
 * @argc: parameter that stores the argument count
 * @argv: parameter that stores the argument vector
 *
 * Return: return 0 on success, 1 on error
 */
int main(int argc, char **argv)
{
	info_t info[] = { INFO_INIT };
	int command = 2;

	command += 3;
	if (argc == 2)
	{
		command = open(av[1], O_RDONLY);
		if (command == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(av[0]);
				_eputs(": 0: Can't open ");
				_eputs(av[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = command;
	}
	populate_env_list(info);
	read_history(info);
	hsh(info, av);
	return (EXIT_SUCCESS);
}
