#include "shell.h"
#include <stdio.h>
#include <signal.h>

/**
 * signal_handler - Handles signals and prints prompt.
 * @sg: The signal number (unused).
 */
void signal_handler(int sg)
{
	(void) sg;

	write(STDERR_FILENO, "\n", 1);
	write(STDERR_FILENO, "$ ", 2);
}

/**
 * handle_file - Reads and executes commands from a file.
 * @filename: The name of the file containing commands.
 */
void handle_file(char *filename)
{
	char *fileContent = NULL;
	char **commandTokens = NULL;
	char *commandBuffer = NULL;
	int i, newlineIndex;


	fileContent = memo_do(4096, NULL);
	fileContent = txtf_read(filename);

	newlineIndex = nline(fileContent);
	commandBuffer = memo_do(4096, NULL);
	while (newlineIndex)
	{
		for (i = 0; i < newlineIndex; i++)
		{
			commandBuffer[i] = fileContent[i];
		}
		commandBuffer[i] = '\0';

		commandTokens = _strtok(commandBuffer, " ");

		execute(commandTokens);
		dbl_matrix_free(commandTokens);

		commandBuffer = _memset(commandBuffer, '\0', newlineIndex);

		buff_shift(fileContent, newlineIndex + 1, 4096);
		newlineIndex = nline(fileContent);
	}
	memo_do(0, fileContent);
}

/**
 * file_handle - Handles command execution from a file or interactive mode.
 * @filename: The name of the file to read commands from, or NULL for interactive mode.
 */
void file_handle(char *filename)
{
	char *buffer = NULL, **tokens = NULL, *delimiter = " \n";
	int exitCode = 0;
	ssize_t lineLength = 0, bufferSize = 4096;

	if (filename)
		handle_file(filename);
	else
	{
		while (1)
		{
			if (isatty(STDIN_FILENO))
				write(STDERR_FILENO, "$ ", 2);

			buffer = memo_do(bufferSize, NULL);

			while ((lineLength = _getline(buffer, STDIN_FILENO)) < 0)
			{
				memo_do(0, buffer);
				exit_do(2, "", -1);
			}

			if (lineLength == 0)
			{
				if (isatty(STDIN_FILENO))
					write(STDERR_FILENO, "\n", 1);
				exit_do(2, "", exitCode);
			}

			if (buffer[lineLength - 1] != '\n')
			{
				memo_do(0, buffer);
				continue;
			}

			if ((_strcmp(buffer, "exit\n")) == 0)
				exit_do(2, "", exitCode);

			tokens = _strtok(buffer, delimiter);
			exitCode = execute(tokens);
			memo_do(0, buffer);
			dbl_matrix_free(tokens);
			enuml(1);
		}
	}
}
