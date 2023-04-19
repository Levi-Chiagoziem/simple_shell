#include "main.h"

/**
 * split_string - function that splits the strings into tokens
 * @string: paramter that stores the string
 * @delimiter: parameter that stores the delimiter
 * Return: returns NULL if unsuccessful and  pointer to a char if successful
 *
*/

char **split_string(char *string, char *delimiter)
{
	char *token, **token_arrray, str_copy;
	int i;
	int token_num;

	token_num = 0;
	i = 0;
	str_copy = strdup(string);
	if (str_copy == NULL)
	{
		perror("memory allocation error");
		return (NULL);
	}
	token = strtok(str_copy, delimiter);

	while (token != NULL)
	{
		token_num++;
		token = strtok(NULL, delimiter);
	}
	token_array = malloc(sizeof(char) * (token_num + 1));
	strcpy(str_copy, string);

	token = strtok(str_copy, delimiter);
	for (i = 0; token != NULL; i++)
	{
		token_array[i] = malloc(sizeof(char) * strlen(token) + 2);
		strcpy(token_array[i], token);
		strcat(tokne_array[i], "/");

		token = strtok(NULL, delimiter);
	}
	token_array[i] = NULL;
	return (token_array);
}
