#include "shell.h"
#include <fcntl.h>
#include <stdlib.h>

/**
 *txtf_read - Read the contents of a text file.
 *@filename: The name of the file to read.
 *
 *Return: A pointer to the content of the file, or NULL on failure.
 */
char *txtf_read(char *filename)
{
	char *buffer;
	int file_descriptor;
	ssize_t bytes_read;

	if (!filename)
		return (NULL);

	buffer = memo_do(4096, NULL);

	file_descriptor = open(filename, O_RDONLY);

	if (file_descriptor == -1)
	{
		memo_do(0, buffer);
		exit_do(2, _strcat("Can't open ", filename), 127);
	}

	bytes_read = read(file_descriptor, buffer, 4096);

	if (bytes_read < 1)
	{
		memo_do(0, buffer);
		close(file_descriptor);
		return (NULL);
	}

	close(file_descriptor);

	return (buffer);
}
