#include "main.h"

char **split_string(char *str, char *delim)
{
	char *str_copy, **pp, *token;
	int i, num_tokens = 0;

	str_copy = strdup(str);
	if (!str_copy)
	{
		perror("split_string function");
		return (NULL);
	}
	token = strtok(str_copy, delim);

	while (token != NULL)
	{
		num_tokens++;
		token = strtok(NULL, delim);
	}

	pp = malloc(sizeof(char *) * (num_tokens + 1));
	if (!pp)
	{
		free_func(&str_copy, 0);
		perror("split_string function");
		return (NULL);
	}

	strcpy(str_copy, str);
	token = strtok(str_copy, delim);

	for (i = 0; token != NULL; i++)
	{
		pp[i] = malloc(sizeof(char) * strlen(token) + 2);

		if (!pp[i])
		{
			free_func(pp, i);
			free_func(&str_copy, 0);
			perror("split_string function");
			return (NULL);
		}
		strcpy(pp[i], token);
		strcat(pp[i], "/");

		token = strtok(NULL, delim);
	}
	pp[i] = NULL;
	free_func(&str_copy, 0);
	return (pp);
}
