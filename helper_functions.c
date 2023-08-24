#include "helper_functions.h"

#include <stdio.h>
#include <stdlib.h>

/**
 * custom_getline - A custom implementation of getline.
 * @lineptr: A pointer to the buffer where the line is stored.
 * @n: A pointer to the size of the buffer.
 * @stream: The input stream to read from.
 *
 * Return: The number of characters read, or -1 on failure.
 */
ssize_t custom_getline(char **lineptr, size_t *n, FILE *stream)
{
ssize_t nread;

nread = getline(lineptr, n, stream);

if (nread == -1)
{
if (feof(stream))
{
printf("\n");
}
else
{
perror("custom_getline");
exit(EXIT_FAILURE);
}
}
else if ((*lineptr)[nread - 1] == '\n')
{
(*lineptr)[nread - 1] = '\0';
}

return (nread);
}
