#include "helpers.h"

/**
 * handle_builtin_commands - Check and execute builtin commands.
 * @args: An array of strings representing the command and its arguments.
 *
 * Return: 0 if a builtin command was executed, 1 otherwise.
 */
int handle_builtin_commands(char **args)
{
if (strcmp(args[0], "exit") == 0)
{
return (0);
}
else if (strcmp(args[0], "setenv") == 0)
{
return (1);
}
else if (strcmp(args[0], "unsetenv") == 0)
{
return (1);
}
return (1);
}
