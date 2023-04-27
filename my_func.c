#include "main.h"
#define LINE_BUF 1024


/**
 * isDel - Function to check if char is a valid delimiter
 * @delims: String containing all delimiters
 * @c: Character to check
 * Return: 1 if c is a valid delimiter else 0
 */
short int isDel(const char *delims, char c)
{
	while (*delims)
	{
		if (c == *delims)
			return (1);
		delims++;
	}
	return (0);
}

/**
 * _strtok - Implementation of built-in strtok, converts string to tokens.
 * @delim: String containing all delimiters to split string with
 * @str: String to delmit.
 * Return: Pointer to next token in string or NULL if there are no more.
 */
char *_strtok(char *str, const char *delim)
{
	static char *curr_ptr;
	char *tmp = NULL;
	int i = 0;

	if (!delim)
		return (NULL);

	if (str && *str)
		curr_ptr = str;

	while (curr_ptr && curr_ptr[i])
	{
		if (!isDel(delim, curr_ptr[i]))
		{
			tmp = curr_ptr[i] ? &curr_ptr[i] : curr_ptr;

			while (curr_ptr[++i])
			{
				if (isDel(delim, curr_ptr[i]))
				{
					curr_ptr[i] = 0;
					curr_ptr = curr_ptr[i + 1] ? &curr_ptr[i + 1] : NULL;
					return (tmp);
				}
			}
			curr_ptr = NULL;
			return (tmp);
		}
		i++;
	}
	return (NULL);
}


/**
 * read_to_buf - Function to copy all content from a file to a malloc'd buffer.
 * @fd: Fildes to use
 * @lineptr: Pointer to Buffer to store text
 * @n: Size of buffer pointed to by lineptr
 * Return: Buffer conatining entire text from fildes or NULL if failed.
 */

char *read_to_buf(int fd, char **lineptr, size_t *n)
{
	char buf[LINE_BUF + 1] = {0};
	char *ptr = *lineptr;
	ssize_t count = 0;
	size_t tot = 0;
	unsigned int prev_size = 0;

	do {
		count = read(fd, buf, LINE_BUF);
		if (count == -1)
			return (NULL);
		if (count == 0)
			return (NULL);
		while (fd == STDIN_FILENO && !_strchr(buf, '\n'))
		{
			if (_strlen(buf) == 0)
				return (NULL);
			count += read(fd, (buf + count), (LINE_BUF - count));
			if (count == LINE_BUF)
				break;
		}
		if (count + tot > *n)
		{
			ptr = _realloc(ptr, prev_size, (sizeof(*ptr) * (*n + count + 1)));
			if (!ptr)
				return (NULL);
			prev_size = (sizeof(*ptr) * (*n + count + 1));
		}
		_memcpy((ptr + tot), buf, count);
		tot += count;
		ptr[tot] = '\0';
		*n += count;

	} while (count == LINE_BUF);
	*lineptr = ptr;
	return (ptr);
}


/**
 * _getline - Implementation of getline Fn using only read.
 * @fd: Fildes to use
 * @lineptr: Pointer to Buffer to store text
 * @n: Size of buffer pointed to by lineptr
 * Return: Size of line read excluding newline else -1 if failed.
 */

ssize_t _getline(char **lineptr, size_t *n, int fd)
{
	static char **line_stat_ptr, *tot_stream;
	static size_t f_cnt;
	char *lines = NULL;

	if (!lineptr || !n)
	{
		errno = EINVAL;
		return (-1);
	}
	if (!line_stat_ptr)
		line_stat_ptr = lineptr;
	if (f_cnt == 0 || fd == STDIN_FILENO)
	{
		tot_stream = read_to_buf(fd, lineptr, n);
		if (!tot_stream)
			return (-1);
		*lineptr = tot_stream;
	}
	lines = !f_cnt++ || fd == 0 ? _strtok(*lineptr, "\n") : _strtok(NULL, "\n");
	if (!lines)
	{
		*lineptr = tot_stream;
		f_cnt = 0;
		return (-1);
	}
	*lineptr = lines;
	return (_strlen(*lineptr));
}
