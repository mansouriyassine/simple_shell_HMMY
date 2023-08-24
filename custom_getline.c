#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "shell.h"

/**
 * custom_read_line - Read a line of input from the user using a custom buffer.
 *
 * Return: The input line as a string.
 */
char *custom_read_line(void)
{
size_t bufsize = 0;
ssize_t bytes_read;
char *line = NULL;

bytes_read = read(STDIN_FILENO, line, bufsize);
if (bytes_read == -1)
{
perror("read");
exit(EXIT_FAILURE);
}
if (bytes_read == 0)
{
exit(EXIT_SUCCESS);
}
return (line);
}
