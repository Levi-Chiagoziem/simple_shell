#include "main.h"

/**
  * tokens_to_arr - This function creates an array of strings from tokens
  * @command_copy: This holds a copy of string to be tokenized
  * @num_tokens: The number of tokens present in the string.
  * @delim: The delimiter to be used.
  * Return: Pointer to Pointer of strings or NULL.
 */

char **tokens_to_arr(char *command_copy, int num_tokens, const char *delim)
{
	char **args = NULL, *token = NULL;
	int i = 0;

	args = malloc(sizeof(char *) * (num_tokens + 1));
	if (args == NULL)
	{
		free_func(&command_copy, 0);
		perror("Error: line_to_args1");
		return (NULL);
	}

	token = strtok(command_copy, delim);
	for (i = 0; token != NULL; i++)
	{
		args[i] = malloc(sizeof(char) * (strlen(token) + 1));
		if (args[i] == NULL)
		{
			free_func(&command_copy, 0);
			free_func(args, i);
			perror("Error: line_to_args2");
			return (NULL);
		}

		strcpy(args[i], token);
		token = strtok(NULL, delim);
	}
	args[num_tokens] = NULL;
	return (args);
}

/**
 * line_to_args - function that converts a comnand strind to a string of tokens
 * @command: parameter that stores the command
 * @delim: parameter that stors the delimiter
 * Return: returns a pointer to a pointer of a char i an array of tokens
 *
*/

char **line_to_args(char *command, const char *delim)
{
	char *command_copy = NULL, *token = NULL, **args = NULL;
	int num_tokens = 0;

	command_copy = strdup(command);
	if (command_copy == NULL)
	{
		perror("Error: line_to_args");
		return (NULL);
	}

	token = strtok(command, delim);
	if (token == NULL)
	{
		free_func(&command_copy, 0);
		return (NULL);
	}

	while (token)
	{
		num_tokens++;
		token = strtok(NULL, delim);
	}
	args = tokens_to_arr(command_copy, num_tokens, delim);
	free_func(&command_copy, 0);
	return (args);
}

