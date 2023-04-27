#include "main.h"

/**
  * _strcat - Concatenates two strings.
  * @dest: Destination param.
  * @src: Source param.
  * Return: Pointer to resulting dest
  */

char *_strcat(char *dest, char *src)
{
	char *destCopy = dest;
	int destEnd = 0;

	while (*src)
	{
		if (*destCopy == '\0' && !destEnd)
			destEnd = 1;
		if (destEnd)
		{
			*destCopy = *src;
			src++;
		}
		destCopy++;
	}
	*destCopy = '\0';
	return (dest);
}

/**
  * _strcpy - Copies a string from src to destination.
  * @dest: Destination param.
  * @src: Source param.
  * Return: Pointer to dest
  */

char *_strcpy(char *dest, char *src)
{
	char *destCopy = dest;

	while (*src != '\0')
	{
		*destCopy = *src;
		src++;
		destCopy++;
		if (*src == '\0')
			*destCopy = *src;
	}
	return (dest);
}


/**
  * _strdup - Duplicates a given string.
  * @s: The string.
  * Return: Pointer to duplicate, else NULL
  */

char *_strdup(const char *s)
{
	char *new_str = NULL;
	size_t lenS = _strlen(s);

	new_str = malloc(sizeof(*new_str) * (lenS + 1));
	if (!new_str)
		return (NULL);
	new_str = strcpy(new_str, s);
	return (new_str);
}


/**
  * _strncpy - Copies src string into dest upto a given n.
  * @dest: Destination param.
  * @src: Source param.
  * @n: Number of bytes to use in src
  * Return: Pointer to resulting dest
  */

char *_strncpy(char *dest, char *src, int n)
{
	int i = 0, srcEnd = 0;

	while (i < n)
	{
		if (src[i] && !srcEnd)
			dest[i] = src[i];
		else
		{
			dest[i] = '\0';
			srcEnd = 1;
		}
		i++;
	}
	return (dest);
}
