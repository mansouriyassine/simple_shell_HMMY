#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

/**
 * enuml - Increment and return a static variable.
 * @add: The value to add to the static variable.
 *
 * Return: The updated value of the static variable.
 */
int enuml(int add)
{
	static int cmdline;

	cmdline += add;
	return (cmdline);
}

/**
 * prg_nm - Return a static variable.
 * @name: The string to set the static variable to.
 *
 * Return: The value of the static variable.
 */
char *prg_nm(char *name)
{
	static char *resf;

	if (!resf)
	{
		resf = name;
	}

	return (resf);
}

/**
 * error_handle - Handle and display error messages.
 * @command: The command that triggered the error.
 * @status: The status code of the error.
 * @extra: Additional information to display (optional).
 *
 * This function handles and displays error messages based on the provided
 * command, status code, and extra information. It constructs and writes an
 * error message to the standard error output.
 */
void error_handle(char *command, int status, char *extra)
{
	char *name = NULL;
	char *err_msg = NULL;
	char *cmdline = NULL;

	name = prg_nm(NULL);
	cmdline = _itoa(enuml(0));

	write(STDERR_FILENO, name, _strlen(name));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, cmdline, _strlen(cmdline));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, command, _strlen(command));
	write(STDERR_FILENO, ": ", 2);

	if (status == 2)
	{
		err_msg = "not found";
	}
	else if (status == 126 || status == 127)
	{
		err_msg = "Permission denied";
	}
	else if (status == 9000)
	{
		err_msg = "Illegal number: ";
	}
	else
	{
		err_msg = "Unknown error occurred.";
	}

	write(STDERR_FILENO, err_msg, _strlen(err_msg));

	if (extra)
	{
		write(STDERR_FILENO, extra, _strlen(extra));
	}

	write(STDERR_FILENO, "\n", 1);
}

/**
 * main - Entry point of the program.
 * @argc: The number of command-line arguments.
 * @argv: An array of strings containing the arguments.
 * @envp: An array of strings containing the environment variables.
 *
 * Return: Always 0.
 */
int main(int argc, char **argv, char **envp)
{
	char *filename = NULL;

	prg_nm(argv[0]);

	if (argc > 2)
		return (-1);

	filename = (argv && argv[1]) ? argv[1] : NULL;

	signal(SIGINT, signal_handler);

	envrt_do((char *) envp, NULL);

	enuml(1);

	file_handle(filename);
	return (0);
}

