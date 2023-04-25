#include "main.h"
/**
 * exit-shell - Exit shell. Status default zero
 * @args: arguments
 *
 * Return: 1
 */
int exit_shell(char **args,
		char __attribute__((unused))**env)
{
	int id = getpid();
	int status = 0;

	if (args[1])
		status = atoi(args[1]);

	if (id != 0)
		exit(status);
	return (1);
}

/**
 * print_env - Prints environment variables
 * @args: arguments
 * @env: enviroment variables
 *
 * Return: 1
 */
int print_env(char __attribute__((unused))**args,
		char __attribute__((unused))**env)
{
	static Node *head, *tmp;
	head = getenv_list();
	
	tmp = head;
	while(tmp->next)
	{
		print_node(tmp);
		write(1, "\n", 1);
		tmp = tmp->next;
	}
	print_node(tmp);
	write(1, "\n", 1);
	return (1);
}

void print_node(Node *ptr)
{
	write(1, ptr->name, strlen(ptr->name));
	write(1, "=", 1);
	write(1, ptr->value, strlen(ptr->value));
}

int set_env(char **args, char __attribute__((unused))**environ)
{
	Node *head = getenv_list(), *tmp, *tmp1;

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
			if (strcmp(tmp->name, args[1]) == 0)
			{
				tmp->value = strdup(args[2]);
				break;
			}
			tmp = tmp->next;
		}
		if (!tmp->next)
		{
			tmp1 = malloc(sizeof(Node));
			tmp1->name = strdup(args[1]);
			tmp1->value = strdup(args[2]);
			tmp1->next = NULL;
			tmp->next = tmp1;
		}
	}
        return (1);	
}

Node *getenv_list(void)
{
	extern char **environ;
	char *env, *name, *value;
        static Node *head;
        Node *tmp = NULL, *tmp1 = NULL;
	int i, j, len;

	if (!head)
	{
		for(i = 0; environ[i]; i++)
		{
			len = 0;
			env = environ[i];
			for (j = 0; env[j] != '='; j++)
			{
				len++;
			}
			name = malloc(sizeof(char) * (len + 1));
			value = env + j + 1;
			strncat(name, env, len);
			tmp = malloc(sizeof(Node));
			tmp->name = strdup(name);
			tmp->value = strdup(value);
			tmp->next = NULL;
			if (!head)
				head = tmp;
			else
			{
				tmp1 = head;
				while(tmp1->next)
				{
					tmp1 = tmp1->next;
				}
				tmp1->next = tmp;
			}
		}
	}
        return (head);
}
int unset_env(char **args, char __attribute__((unused))**env)
{
	Node *head = getenv_list(), *next, *curr;
	int i;

	curr = head;
	for (i = 0; args[i]; i++)
		i++;
	if (i > 2)
	{
		perror("Too many Arguments");
		return (-1);
	}
	while (curr->next)
	{
		next = curr->next;
		if (strcmp(next->name, args[1]) == 0)
		{
			curr->next = NULL;
			curr->next = next->next;
			free_node(next);
			break;
		}
		curr = curr->next;
	}
	if (!curr->next)
	{
		perror("Env not found");
		return (-1);
	}
	return (1);
}


void free_node(Node *ptr)
{
	free(ptr->name);
	free(ptr->value);
	free(ptr);
}
