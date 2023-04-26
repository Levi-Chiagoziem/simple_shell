#include "main.h"
#include <limits.h>

/**
 * count_digits - function that counts digits in the base required
 * @num: parameter that stores the number
 * @base: parameter that stores the required base
 *
 * Return: returns the number of digits.
 */
int count_digits(long num, long base)
{
    int digit_count = 0;

    /*Convert negative num to its absolute value*/
    num = (num < 0) ? -num : num;

    /*Count the number of digits by dividing num by base until num becomes 0*/
    while (num > 0) {
        num /= base;
        digit_count++;
    }

    /* If no digits were counted, the number is 0*/
    if (digit_count == 0)
        digit_count = 1;

    return digit_count;
}
