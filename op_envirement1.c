#include "shell.h"
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>

char *get_env_val(char *);

/**
 * get_dir_path - get the path in a double char pointer
 * Return: the double char pointer of the path
 */
/**
 * get_dir_path - Get the directories listed in the PATH environment variable.
 *
 * Return: A char array containing directories, terminated by NULL.
 */
char **get_dir_path(void)
{
	char *path_env = NULL;
	char **directories = NULL;

	path_env = get_env_val("PATH");
	directories = _strtok(path_env, ":");
	memo_do(0, path_env);

	return (directories);
}


/**
 * get_env_val - Get the value of an environment variable.
 * @name: The name of the environment variable.
 *
 * Return: The value of the environment variable, or NULL if not found.
 */
char *get_env_val(char *name)
{
	int i = 0, j = 0;
	char **environment = NULL;
	char *result = NULL;

	environment = get_env();
	while (environment[i])
	{
	j = 0;
	while (environment[i][j] && name[j])
	{
		if (environment[i][j] != name[j])
			break;
		j++;
	}
	if (name[j] == '\0' && environment[i][j] == '=')
		{
		if (!environment[i][j + 1])
			return (NULL);
		result = memo_do((_strlen((environment[i]) + j + 1) + 1), NULL);
		_strcpy(result, ((environment[i]) + j + 1));
		dbl_matrix_free(environment);
		return (result);
	}
	i++;
	}
	dbl_matrix_free(environment);
	return (NULL);
}

/**
 * finddir_path - Find the directory containing the specified command.
 * @path: Array of directories to search.
 * @command: The command to search for.
 *
 * Return: A pointer to the directory containing the command, or NULL if not found.
 */
char *finddir_path(char **path, char *command)
{
	struct dirent *de = NULL;
	DIR *dr = NULL;
	int i = 0;

	if (!command || !path)
		return (NULL);
	for (i = 0; path[i]; i++)
	{
		dr = opendir(path[i]);

		if (!dr)
		{
			write(STDOUT_FILENO, "Could not open directory\n", 25);
			closedir(dr);
		}
		else
		{
			while ((de = readdir(dr)) != NULL)
			{
				if (_strcmp((*de).d_name, command) == 0)
				{
					closedir(dr);
					return (path[i]);
				}
			}
			closedir(dr);
		}
	}
	return (NULL);
}

/**
 * get_env - Get the current environment as a dynamically allocated char**.
 *
 * Return: The environment as a char**.
 */
char **get_env(void)
{
	return (envrt_do(NULL, NULL));
}

/**
 * all_cmd_get - Get the full command path.
 * @path: The directory path.
 * @command: The command.
 *
 * Return: The concatenated path and command.
 */
char *all_cmd_get(char *path, char *command)
{
	int path_length = 0, command_length = 0;
	char *result = NULL;
	char **split_command = NULL;

	split_command = _strtok(command, "/");
	if (split_command && split_command[0] && split_command[1])
	{
	dbl_matrix_free(split_command);
	return (command);
	}
	dbl_matrix_free(split_command);

	path_length = _strlen(path);
	command_length = _strlen(command);
	result = memo_do(sizeof(char) * (path_length + command_length + 1 + 1), NULL);
	_strcat(result, path);
	_strcat(result, "/");
	_strcat(result, command);

	return (result);
}

