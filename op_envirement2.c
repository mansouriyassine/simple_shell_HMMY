#include "shell.h"

/**
 * envrt_do - Manage environment variables.
 * @add: Environment variable to add.
 * @delete: Environment variable to delete.
 *
 * Return: An array of environment variables.
 */
char **envrt_do(char *add, char *delete)
{
	static sig_list *environment;
	char *tmp = NULL;
	int length = 0, i = 0, j = 0;

	if (!environment)
	{
		environment = lstfy((char **)add);
		return (NULL);
	}

	if (add)
		node_insrt_tail(&environment, add);
	else if (delete)
	{
		length = lenght_lst(environment);
		for (i = 0; i < length; i++)
		{
			j = 0;
			tmp = node_get_index(environment, i)->ptr;
			while (delete && tmp && delete[j] && tmp[j] != '=')
			{
				if (delete[j] != tmp[j])
					break;
				j++;
			}
			if (!(delete[j]) && tmp[j] == '=')
			{
			delete_node_index(&environment, i);
			break;
			}
		}
	}

	return (arrayify_list(environment));
}
