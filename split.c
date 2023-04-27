#include "main.h"

/**
  *split_string -  function that splits the path and append a slash at each end
  *@str: parametr tring to split.
  *@delim: paremeter that stores the delimiter
  *Return: Pointer to Array of NULL-terminated strings
  */

char **split_string(char *str, char *delim)
{
	char *str_copy, **path_token, *token;
	int i, num_tokens = 0;

	str_copy = _strdup(str);
	if (str_copy == NULL)
		return (NULL);
	token = _strtok(str_copy, delim);
	while (token != NULL)
	{
		num_tokens++;
		token = _strtok(NULL, delim);
	}
	path_token = malloc(sizeof(char *) * (num_tokens + 1));
	if (path_token == NULL)
	{
		free_func(&str_copy, 0);
		perror("Error: split_string function");
		return (NULL);
	}
	_strcpy(str_copy, str);
	token = _strtok(str_copy, delim);
	for (i = 0; token != NULL; i++)
	{
		path_token[i] = malloc(sizeof(char) * _strlen(token) + 2);
		if (!path_token[i])
		{
			free_func(path_token, i);
			free_func(&str_copy, 0);
			perror("Erroe: split_string function");
			return (NULL);
		}
		_strcpy(path_token[i], token);
		_strcat(path_token[i], "/");
		token = _strtok(NULL, delim);
	}
	path_token[i] = NULL;
	free_func(&str_copy, 0);
	return (path_token);
}
