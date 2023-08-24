#include "helpers.h"

/**
 * handle_cd_command - Change the current working directory.
 * @args: An array of strings representing the command and its arguments.
 *
 * Return: Always returns 1 to continue the shell loop.
 */
int handle_cd_command(char **args)
{
if (args[1] == NULL)
{
if (chdir(getenv("HOME")) != 0)
{
perror("shell");
}
}
else
{
if (chdir(args[1]) != 0)
{
perror("shell");
}
}

return (1);
}
