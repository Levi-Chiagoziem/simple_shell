#include "main.h"

/**
 * free_node - frees a node
 * @ptr: Pointer to node
 */
void free_node(Node *ptr)
{
	free(ptr->name);
	free(ptr->value);
	free(ptr);
}

/**
 * free_linked_list - frees linked list
 * @head: Head pointer.
 */
void free_linked_list(Node *head)
{
	Node *tmp, *next;

	if (head)
	{
		tmp = head;
		while (tmp->next)
		{
			next = tmp->next;
			free_node(tmp);
			tmp = next;
		}
		free_node(tmp);
	}
}


/**
 * unset_env - removes an envrioment variable
 * @args: Arguments
 * @envs: Environment variables
 *
 * Return: an integer
 */
int unset_env(char **args, char **envs)
{
	Node *head = getenv_list(envs), *next, *curr;
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
		if (_strcmp(next->name, args[1]) == 0)
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
