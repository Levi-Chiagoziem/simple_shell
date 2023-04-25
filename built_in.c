#include "main.h"
#include <unistd.h>

/**
 * check_builtin - function that checks for built in command
 * @args: parameter that stores the command to be checked
 * Return: return O when successful and 1 otherwise
*/
int check_builtin(char **args)
{
	built_in ar[] = {
	{"exit", exit_shell},
		{"env", print_env},
		{NULL, NULL}
	};
	int i;
	char **environ = __environ; /* define environ inside the function*/

	for (i = 0; ar[i].exe; i++)
	{
		if (!strcmp(args[0], ar[i].exe))
		{
			ar[i].func(args, environ);
			return (1);
		}
	}
	return (0);
}

