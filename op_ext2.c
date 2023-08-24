#include "shell.h"
#include <stdio.h>

/**
 *exec_single - Execute a single command.
 *@tokens: Array of command tokens.
 *
 *Return: The exit status indicating success or failure.
 */
int exec_single(char **tokens)
{
	char **builtin_commands = NULL;
	int result = 1, i = 0, builtin_index = 0;

	if (!tokens || !tokens[0])
		return (0);

	builtin_commands = get_builtins();

	for (i = 0; builtin_commands[i]; i++)
	{
		if (_strcmp(builtin_commands[i], tokens[0]) == 0)
		{
			builtin_index = i + 1;
			break;
		}
	}

	if (builtin_index && tokens)
	{
		result = builtinexec(tokens, builtin_index);
	}
	else if (tokens)
	{
		result = nmbr_ext(tokens);
	}

	return (result);
}

/**
 *get_next_commands - Get the next set of coe or logical operator.
 *@tokens: Array of command tokens.
 *
 *Return: An array of command next commands, or NULL if not found.
 */
char **get_next_commands(char **tokens)
{
	char **next_commands = NULL;
	int command_size = 0, ret_size = 0, i = 0;

	if (!tokens || !(tokens[0]))
		return (NULL);

	command_size = cmd_size(tokens);

	if (!(tokens[command_size]) || !(tokens[command_size + 1]))
		return (NULL);

	while (tokens[command_size + 1 + ret_size])
		ret_size++;

	next_commands = memo_do(sizeof(char *) * (ret_size + 1), NULL);

	for (i = 0; i < ret_size; i++)
	{
		next_commands[i] = memo_do(_strlen(tokens[command_size + 1 + i]) + 1, NULL);
		_strcpy(next_commands[i], tokens[command_size + 1 + i]);
	}

	next_commands[i] = NULL;
	return (next_commands);
}

/**
 *get_current_command - Get the cur pipe or logical operator.
 *@tokens: Array of command tokens.
 *
 *Return: An array of  command, or NULL if not found.
 */
char **get_current_command(char **tokens)
{
	char **current_command = NULL;
	int command_size = 0, i = 0;

	if (!tokens || !(tokens[0]))
		return (NULL);

	command_size = cmd_size(tokens);

	if (!command_size)
		return (NULL);

	current_command = memo_do(sizeof(char *) * (command_size + 1), NULL);

	for (i = 0; i < command_size; i++)
	{
		current_command[i] = memo_do(_strlen(tokens[i]) + 1, NULL);
		_strcpy(current_command[i], tokens[i]);
	}

	current_command[i] = NULL;
	return (current_command);
}

/**
 *execute - Execute a sequence of commands.
 *@tokens: Array of command tokens.
 *
 *Return: The exit status indicating success or failure.
 */
int execute(char **tokens)
{
	int result = 0, operator = 0;
	char **current_commands = NULL;
	char **next_commands = NULL;

	operator = ops_srch(tokens);
	current_commands = get_current_command(tokens);
	next_commands = get_next_commands(tokens);

	while (1)
	{
		if (!current_commands || !(current_commands[0]))
			return (result);

		result = exec_single(current_commands);

		if (operator == 3 && !result)
			return (result);
		if (operator == 2 && result)
			return (result);

		operator = ops_srch(next_commands);
		current_commands = get_current_command(next_commands);
		next_commands = get_next_commands(next_commands);
	}

	return (1);
}
