#include "shell.h"

/**
 *builtinenv - Print the environment variables.
 *
 *Return: Always 0.
 */
int builtinenv(void)
{
	char **env = get_env();
	int i = 0;

	while (env[i])
	{
		write(STDOUT_FILENO, env[i], _strlen(env[i]));
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}

	dbl_matrix_free(env);
	return (0);
}

/**
 *get_builtins - Get a list of built-in command strings.
 *
 *Return: A char array containing built-in command strings, terminated by NULL.
 */
char **get_builtins(void)
{
	char **builtins;

	builtins = memo_do(sizeof(char *) * 6, NULL);

	builtins[0] = "exit";
	builtins[1] = "cd";
	builtins[2] = "env";
	builtins[3] = "setenv";
	builtins[4] = "unsetenv";
	builtins[5] = NULL;
	return (builtins);
}

/**
 *setenv_builtin - Set an environment variable.
 *@tokens: Array of command tokens.
 *
 *Return: 0 on success, 1 on failure.
 */
int setenv_builtin(char **tokens)
{
	char *rof = NULL;

	if (!tokens[1] || !tokens[2])
	{
		error_handle(tokens[0], 3001, NULL);
		return (1);
	}

	envrt_do(NULL, tokens[1]);

	rof = memo_do(_strlen(tokens[1]) + _strlen(tokens[2]) + 2, NULL);
	_strcat(rof, tokens[1]);
	_strcat(rof, "=");
	_strcat(rof, tokens[2]);
	envrt_do(rof, NULL);

	return (0);
}

/**
 *builtinunsetenv - Unset an environment variable.
 *@tokens: Array of command tokens.
 *
 *Return: 0 on success, 1 on failure.
 */
int builtinunsetenv(char **tokens)
{
	if (!tokens[1])
	{
		error_handle(tokens[0], 3002, NULL);
		return (1);
	}

	envrt_do(NULL, tokens[1]);

	return (0);
}

/**
 *builtincd - Change the current working directory.
 *@tokens: Command input into prompt tokenized.
 *
 *Return: The exit status.
 */
int builtincd(char **tokens)
{
	char *home_env = NULL, *temp_lastdir;
	static char *last_directory;

	(void) home_env;

	if (!last_directory)
		last_directory = memo_do(100, NULL);
	temp_lastdir = memo_do(100, NULL);

	if (tokens[1] && _strcmp(tokens[1], "-") == 0)
	{
		getcwd(temp_lastdir, 100);
		chdir(last_directory);
		write(STDOUT_FILENO, last_directory, _strlen(last_directory));
		write(STDOUT_FILENO, "\n", 1);
		last_directory = temp_lastdir;
	}
	else if (tokens[1])
	{
		getcwd(last_directory, 100);
		chdir(tokens[1]);
	}
	else
	{
		getcwd(last_directory, 100);
		chdir(get_env_val("HOME"));
	}

	return (0);
}
