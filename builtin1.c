#include "main.h"

/**
 * check_builtin - check if its a builtin function
 * @args: arguments
 * @environ: environment variables
 * @argv: A NULL-terminated arr of str passed into the CLI
 * @lineptr: This holds the string(line) to be split to args
 *
 * Return: 1 for Success and 0 for failure
 */
int check_builtin(char **args, char **environ, char **argv, char **lineptr)
{
	built_in ar[] = {
		{"env", print_env},
		{"unsetenv", unset_env},
		{"setenv", set_env},
		{NULL, NULL}
	};
	int i;

	for (i = 0; ar[i].exe; i++)
	{
		if (!_strcmp(args[0], ar[i].exe))
		{
			ar[i].func(args, environ);
			return (1);
		}
		else if (!_strcmp(args[0], "exit"))
		{
			return (exit_shell(args, environ, argv, lineptr));
		}
	}
	return (0);

}
