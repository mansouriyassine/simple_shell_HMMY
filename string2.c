#include "shell.h"
#include <stdio.h>



/**
 * cmd_size - Calculate the size of a command.
 * @tokens: The input tokens.
 * Return: The size of the command.
 */
int cmd_size(char **tokens)
{
	int size = 0;

	if (!tokens)
		return (0);

	for (size = 0; tokens[size]; size++)
	{
		if (tokens[size][0] == '&' && tokens[size][1] == '&')
			break;
		if (tokens[size][0] == '|' && tokens[size][1] == '|')
			break;
		if (tokens[size][0] == ';')
			break;
	}

	return (size);
}


/**
 * _atoi - Convert a string to an integer.
 * @s: The input string.
 * Return: The converted integer.
 */

int _atoi(char *s)
{
	int num, len, numcount, mult, x, neg;

	len = 0;
	x = 0;
	numcount = 0;
	mult = 1;
	neg = 1;
	num = 0;

	while (s[len] != '\0')
	{
		if (s[len] >= '0' && s[len] <= '9')
		{
			numcount++;
			if (!(s[len + 1] >= '0' && s[len + 1] <= '9'))
				break;
		}
		len++;
	}
	for (; numcount > 1; numcount--)
		mult *= 10;
	for (; x <= len; x++)
	{
		if (s[x] == '-')
			neg *= -1;
		else if (s[x] <= '9' && s[x] >= '0')
		{
			num += (s[x] - '0') * mult * neg;
			mult /= 10;
		}
	}
	return (num);
}

int _isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);

	return (0);
}

/**
 * nline - Find the index of the first newline character in a string.
 * @input: The input string.
 * Return: The index of the first newline character, or the length of the string if not found.
 */
int nline(char *input)
{
	int i;

	if (!input)
		return (-1);

	for (i = 0; input[i]; i++)
	{
		if (input[i] == '\n')
			return (i);
	}

	return (i);
}

/**
 * buff_shift - Shift the content of an array starting from newline_index and fill the rest with null terminators.
 * @input: The input character array.
 * @newline_index: The index from which to start shifting.
 * @filled: The total size of the array.
 */
void buff_shift(char *input, int newline_index, int filled)
{
	int i, j;

	for (i = newline_index, j = 0; i < filled; i++, j++)
	{
		input[j] = input[i];
	}

	for (; j < filled; j++)
	{
		input[j] = '\0';
	}
}
