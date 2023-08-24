#include "shell.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

/**
 * else_handle_input - if buffer does not include \n or EOF
 * @lineptr: the buffer to put the data in
 * @stream: the stream to read from
 * @input: buffer
 * @filled: size of buffer
 * Return: _getline function
 */
ssize_t else_handle_input(char *lineptr, int stream, char *input, int filled)
{
	int bufc;
	char container;

	if (filled == 4096)
	{
	for (bufc = 1; bufc && container != '\n';)
	{
	container = 0;
	bufc = read(stream, &container, 1);
	}
		input[4095] = '\n';
		return (_getline(lineptr, stream));
	}
	else
	{
		bufc = read(stream, input + filled, 4096 - filled);
		input[filled + bufc] = (bufc < (4096 - filled)) ?
			'\n' :
			input[filled + bufc];

		filled = filled + bufc + 1;
		return (_getline(lineptr, stream));
	}
}

/**
 * _getline - Read a line from a stream.
 * @lineptr: A pointer to the buffer where the line will be stored.
 * @stream: The file stream to read from.
 *
 * Return: The number of bytes read, -1 on error, or 0 on EOF.
 */
ssize_t _getline(char *lineptr, int stream)
{
	static char input[4096];
	static int filled, i;
	ssize_t rof = 0;
	int newline_index;

	if (!filled)
	{
		int bufc;

		while ((bufc = read(stream, input, 4096)) < 0)
		{
			perror("Read Error\n");
			return (-1);
		}
	filled = bufc;
	if (!bufc)
	return (0);
	}


	newline_index = nline(input);

	if (newline_index != -1)
	{
	rof = newline_index;
	if (input[rof] == '\n')
		rof++;
	buff_shift(input, newline_index + 1, filled);
	filled -= rof;
	for (i = 0; i <= newline_index; i++)
		lineptr[i] = input[i];
	return (rof);
	}
	else
	{
	else_handle_input(lineptr, stream, input, filled);
	return (-1);
	}
}
