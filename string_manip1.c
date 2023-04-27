#include "main.h"

/**
  * _strchr - Locates a character in a string.
  * @s: Pointer to string.
  * @c: Character to be found.
  * Return: Pointer to first occurence of char.
  */

char *_strchr(char *s, char c)
{
	while (*s)
	{
		if (*s == c)
			return (s);
		s++;
	}
	return (*s == c ? s : NULL);
}

/**
  * _strlen - Determines a string length.
  * @s: Pointer to the string.
  * Return: Length of the string
  */

int _strlen(const char *s)
{
	const char *command = s;

	while (*command != '\0')
		command++;

	return (command - s);
}

/**
  * _strcmp - Compares two strings.
  * @s1: The first string.
  * @s2: The second string.
  * Return: 0 if equal, else integer value of difference
  */

int _strcmp(char *s1, char *s2)
{
	int cmp = 0, i = 0, diff;

	while (s1[i] && s2[i])
	{
		diff = s1[i] - s2[i];
		if ((diff < cmp) && cmp <= 0)
			cmp = diff;
		else if ((diff > cmp) && cmp >= 0)
			cmp = diff;
		i++;
	}
	return (cmp);
}

/**
  * _strncmp - Compares two strings.
  * @s1: The first string.
  * @s2: The second string.
  * @n: Number of bytes to compare
  * Return: 0 if equal, else integer value of difference
  */

int _strncmp(char *s1, char *s2, size_t n)
{
	int cmp = 0, i = 0, diff;

	while (s1[i] && s2[i] && n--)
	{
		diff = s1[i] - s2[i];
		if ((diff < cmp) && cmp <= 0)
			cmp = diff;
		else if ((diff > cmp) && cmp >= 0)
			cmp = diff;
		i++;
	}
	return (cmp);
}

/**
  * _strncat - Concatenates two strings upto a given n.
  * @dest: Destination param.
  * @src: Source param.
  * @n: Number of bytes to use in src
  * Return: Pointer to resulting dest
  */

char *_strncat(char *dest, char *src, int n)
{
	char *destCopy = dest;
	int destEnd = 0, i = 0;

	while (*src && i < n)
	{
		if (*destCopy == '\0' && !destEnd)
			destEnd = 1;
		if (destEnd)
		{
			*destCopy = *src;
			src++;
			i++;
		}
		destCopy++;
	}
	return (dest);
}

