#include "shell.h"
#include <string.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * builtinexec - Execute built-in commands based on the given case.
 * @tokens: Array of command tokens.
 * @bcase: The case for the built-in command.
 *
 * Return: The exit status or a value indicating success/failure.
 */
int builtinexec(char **tokens, int bcase)
{
	int exit_status = 0;
	int i = 0;

	switch (bcase)
	{
		case 1:
		{
			if (tokens[1])
			{
				for (; tokens[1][i]; i++)
				{
					if (!_isdigit(tokens[1][i]))
					{
					exit_do(2, "numeric arguments only\n", exit_status);
					}
				}
				exit_status = _atoi(tokens[1]);
			}
			exit_do(2, "", exit_status);
			break;
		}
		case 2:
			return (builtincd(tokens));
		case 3:
			return (builtinenv());
		case 4:
			return (setenv_builtin(tokens));
		case 5:
			return (builtinunsetenv(tokens));
	}

	return (0);
}

/**
 * acc_check - Check access permissions for a command.
 * @comm: The command's path.
 * @token: The token representing the command.
 *
 * Return: The exit status indicating the result of access checks.
 */
int acc_check(char *comm, char *token)
{
	int access_code = 0;

	access_code = access(comm, F_OK);
	if (access_code)
	{
	error_handle(token, 2, NULL);
	return (2);
	}

	access_code = access(comm, X_OK);
	if (access_code)
	{
	error_handle(token, 126, NULL);
	return (126);
	}

	return (0);
}

/**
 * exec_prp - Prepare the command for execution.
 * @token: The token representing the command.
 *
 * Return: The prepared command path.
 */
char *exec_prp(char *token)
{
	char **env_vars = NULL;
	char *prepared_command = NULL;
	char *current_working_dir = NULL;
	char *command_path = NULL;
	int access_code = 0;

	current_working_dir = memo_do(100, NULL);
	prepared_command = all_cmd_get(current_working_dir, token);
	access_code = access(prepared_command, F_OK);

	if (access_code)
	{
	env_vars = get_dir_path();
	command_path = finddir_path(env_vars, token);
	prepared_command = all_cmd_get(command_path, token);
	dbl_matrix_free(env_vars);
	}

	return (prepared_command);
}

/**
 * nmbr_ext - Execute a command and wait for it to finish.
 * @tokens: Array of command tokens.
 *
 * Return: The exit status of the executed command.
 */
int nmbr_ext(char **tokens)
{
	char *prepared_command = NULL;
	pid_t child_pid, wait_id;
	int status = 0, access_code = 0;

	prepared_command = exec_prp(tokens[0]);
	while ((access_code = acc_check(prepared_command, tokens[0])))
		return (access_code);

	child_pid = fork();

	if (child_pid == -1)
		exit_do(2, "Fork failed", EXIT_FAILURE);

	if (!child_pid)
	{
	execve(prepared_command, tokens, (char *const *)get_env());
	perror("");
	exit_do(2, "Couldn't exec", EXIT_FAILURE);
	}
	else
	{
	do {
		wait_id = waitpid(child_pid, &status, WUNTRACED);
		if (wait_id == -1)
		{
			perror("waitpid");
			exit_do(STDERR_FILENO, "", EXIT_FAILURE);
		}
	} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	memo_do(0, prepared_command);
	}

	return (status);
}


/**
 * ops_srch - Search for command operators in tokens.
 * @tokens: Array of command tokens.
 *
 * Return: (1 for ;, 2 for &&, 3 for ||, 0 otherwise).
 */
int ops_srch(char **tokens)
{
	int i = 0;

	if (!tokens)
	{
		return (0);
	}

	for (i = 0; tokens[i]; i++)
	{
	if (tokens[i][0] == ';')
		return (1);
	if (tokens[i][0] == '&' && tokens[i][1] && tokens[i][1] == '&')
		return (2);
	if (tokens[i][0] == '|' && tokens[i][1] && tokens[i][1] == '|')
		return (3);
	}

	return (0);
}
