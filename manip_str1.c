#include "main.h"

/**
 * count_digits - Count the number of digits in the given base
 * @num: The number to count digits for
 * @base: The base to count digits in
 *
 * Return: Number of digits in the given base
 */
int count_digits(long num, long base)
{
	int count = 0;

	num = num >= 0 ? num : -num;
	while (num != 0)
	{
		count++;
		num /= base;
	}
	return (count);
}
