#include "main.h"

int check_builtin(char **args)
{
	built_in ar[] = {
		{"exit", exit_shell},
		{"env", print_env},
		{NULL, NULL}
	};
	int i;
	extern char **environ;
	
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
