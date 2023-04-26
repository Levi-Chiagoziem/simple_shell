#include "main.h"
#include <limits.h>

/**
 * digTostr - Convert number to a string
 * @num: Number
 *
 * Return: String of number
 */
char *digTostr(long num)
{
	int lenStr = num < 0 ? 1 : 0;
	char *str;

	lenStr += (count_digits(num, 10));

	str = malloc(sizeof(*str) * (lenStr + 1));
	if (!str)
		return (NULL);

	str[lenStr--] = '\0';
	str[0] = num >= 0 ? '0' : '-';
	num = num >= 0 ? num : -(num);

	while (num)
	{
		str[lenStr--] = (num % 10) + '0';
		num /= 10;
	}
	return (str);
}
