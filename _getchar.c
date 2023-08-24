#include <unistd.h>
#include <stdio.h>

/**
 * _getchar - Read a character from standard input.
 *
 * Return: The character read as an unsigned char cast, or EOF on failure.
 */
int _getchar(void)
{
	char c;
	ssize_t result = read(0, &c, 1);

	if (result == 1)
		return ((unsigned char)c);
	else
		return (EOF);
}
