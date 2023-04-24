#include "main.h"

/**
 * main- function that prompts the user for input
 * @argc: parameter that stores the argument count
 * @argv: parameter that stores the argument vector as an array of string
 * Return: return 0 when succesful and 1 when unsuccessful
 *
*/

int cmd_count = 0;
int main (int __attribute__((unused))argc, char *argv[])
{
	char *command= NULL, **args = NULL;
	size_t n = 0;
	ssize_t char_num;
	char *prompt = "($) ";
	const char *delim = " \n";
	
	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(1, prompt, strlen(prompt));

		char_num = getline(&command, &n, stdin);
		if (char_num == -1)
		{
			if (isatty(STDIN_FILENO))
				write(1, "\n", 1);
			break;
		}
		cmd_count++;
		argv = command_to_argv(command, delim);
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

