#include "shell.h"
#include <stdio.h>

/**
 * _strev - Reverses a portion of a character array.
 * @str: Pointer to the beginning of the array.
 * @n: Number of characters to reverse.
 * Return: Pointer to the reversed array.
 */
char *_strev(char *str, int n)
{
	char *begin = str;
	char *end = str + n - 1;
	char container;

	while (begin < end)
	{
		container = *end;
		*end = *begin;
		*begin = container;
		begin++;
		end--;
	}
	return (str);
}


/**
 * _itoa - Converts an integer to a string.
 * @num: The integer to be converted.
 * Return: Pointer to the resulting string.
 */
char *_itoa(int num)
{
	int i = 0, neg = 0, cnum = num, len = 0, remainder = 0;
	char *str;

	for (len = 0; cnum; cnum /= 10)
		len++;

	if (num == 0)
	{
		str = memo_do(2 * sizeof(char), NULL);
		str[i++] = '0';
		str[i] = '\0';
		return (str);
	}

	if (num < 0)
	{
		neg = 1;
		num = -num;
		len++;
	}

	str = memo_do((len + 1) * sizeof(char), NULL);

	while (num != 0)
	{
		remainder = num % 10;
		str[i++] = remainder + '0';
		num = num / 10;
	}

	if (neg)
		str[i++] = '-';

	str[i] = '\0';

	_strev(str, i);

	return (str);
}


/**
 * _memset - Fills the first n bytes of the memory area pointed to by s with
 *           the constant byte c.
 * @s: A pointer to the memory area to be filled.
 * @b: The constant byte to fill the memory area with.
 * @n: The number of bytes to be filled.
 *
 * Return: A pointer to the filled memory area.
 */

char *_memset(char *s, char b, int n)
{
	char *p = s;

	for (; n != 0; p++, n--)
		*p = b;
	return (s);
}
