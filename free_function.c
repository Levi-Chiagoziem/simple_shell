#include "main.h"

/**
 * free_func - function that frees up dynamically allocated  space
 * @ptr: parameter that stores the pointer or Array of ptrs to be freed
 * @length: return the size of  argument to be freed or -1 otherwise
 */

void free_func(char **ptr, int length)
{
	int i = 0;

	if (length == 0)
		free(*ptr);
	else if (length > 0)
	{
		while (ptr && *ptr && i < length)
			free(ptr[i++]);
		free(ptr);
	}
	else if (ptr && length == -1)
	{
		while (ptr && *ptr && ptr[i])
		{
			free(ptr[i++]);
			if (ptr[i] == NULL)
				free(ptr[i]);
		}
		free(ptr);
	}
}
