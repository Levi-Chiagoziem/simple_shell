#include "main.h"

/**
 * main - function tests and calls all the others function
 * @argc: parameter that stores the number of argument
 * @argv: parameter that stores a an array of argument
 * Return: return 0 when successful and 1 otherwise
*/

int cmd_count = 0;
int main(int __attribute__((unused))argc, char *argv[])
{
	char *command = NULL, **args = NULL;
	size_t n = 0;
	ssize_t char_no;
	char *prompt = "($) ";
	const char *delim = " \n";

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(1, prompt, strlen(prompt));

		char_no = getline(&command, &n, stdin);
		if (char_no == -1)
		{
			if (isatty(STDIN_FILENO))
				write(1, "\n", 1);
			break;
		}
		cmd_count++;
		args = line_to_args(command, delim);
		if (args == NULL)
		{
			free_func(&command, 0);
			continue;
		}
		if (check_builtin(args))
			continue;

		execmd(argv, args);
		free_func(args, -1);

	}
	free_func(&command, 0);
	return (0);
}

