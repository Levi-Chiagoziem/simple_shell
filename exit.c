#include "main.h"

/**
 * exit_shell - Exit shell. Status default zero
 * @args: arguments
 * @envs: Enviroment variables
 * @argv: A NULL-terminated arr of str passed into the CLI
 * @l_ptr: This holds the string(line) to be split to args
 *
 * Return: 1
 */
int exit_shell(char **args, char **envs, char **argv, char **l_ptr)
{
	int id = getpid();
	int status = 0;
	Node *head = getenv_list(envs);

	if (args[1])
	{
		status = _atoi_cust(args[1]);
		if (status == -1)
		{
			custom_err(args[0], argv, args, 1);
			return (2);
		}
	}
	if (id != 0)
	{
		free_linked_list(head);
		free_func(args, -1);
		free_func(l_ptr, 0);
		exit(status);
	}
	return (1);
}

/**
 * print_env - Prints environment variables
 * @args: arguments
 * @envs: enviroment variables
 *
 * Return: 1
 */
int print_env(char __attribute__((unused))**args, char **envs)
{
	static Node *head, *tmp;

	head = getenv_list(envs);
	tmp = head;
	while (tmp->next)
	{
		print_node(tmp);
		write(1, "\n", 1);
		tmp = tmp->next;
	}
	print_node(tmp);
	write(1, "\n", 1);
	return (1);
}

/**
 * print_node - Prints a single env
 * @ptr: Node pointer
 */
void print_node(Node *ptr)
{
	write(1, ptr->name, _strlen(ptr->name));
	write(1, "=", 1);
	write(1, ptr->value, _strlen(ptr->value));
}

/**
 * set_env - Set environment variable
 * @args: arguments
 * @envs: enviroment variable
 *
 * Return: an Integer
 */
int set_env(char **args, char __attribute__((unused))**envs)
{
	Node *head = getenv_list(envs), *tmp, *tmp1;

	if (!args[1])
	{
		perror("No VARIABLE passed");
		return (-1);
	}
	if (!args[2])
	{
		perror("No VALUE passed");
		return (-1);
	}
	if (args[1] && args[2])
	{
		tmp = head;
		while (tmp->next)
		{
			if (_strcmp(tmp->name, args[1]) == 0)
			{
				tmp->value = _strdup(args[2]);
				break;
			}
			tmp = tmp->next;
		}
		if (!tmp->next)
		{
			tmp1 = malloc(sizeof(Node));
			tmp1->name = _strdup(args[1]);
			tmp1->value = _strdup(args[2]);
			tmp1->next = NULL;
			tmp->next = tmp1;
		}
	}
	return (1);
}
/**
 * getenv_list - Get the enviroment variables and convert
 *		to linked list.
 * @environ: Enviroment variables
 * Return: Pointer to the head pointer.
 */
Node *getenv_list(char **environ)
{
	char *env = NULL, *name = NULL, *value = NULL;
	static Node *head;
	Node *tmp = NULL, *tmp1 = NULL;
	int i, j, len;

	if (!head)
	{
		for (i = 0; environ[i]; i++)
		{
			len = 0;
			env = environ[i];
			for (j = 0; env[j] != '='; j++)
			{
				len++;
			}
			name = malloc(sizeof(char) * (len + 1));
			value = env + j + 1;
			_strncpy(name, env, len);
			tmp = malloc(sizeof(Node));
			tmp->name = name;
			tmp->value = _strdup(value);
			tmp->next = NULL;
			if (!head)
				head = tmp;
			else
			{
				tmp1 = head;
				while (tmp1->next)
				{
					tmp1 = tmp1->next;
				}
				tmp1->next = tmp;
			}
		}
	}
	return (head);
}
