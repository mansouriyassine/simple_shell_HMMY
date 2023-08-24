#include "helpers.h"

/**
 * read_line - Read a line of input from the user.
 *
 * Return: The input line as a string.
 */
char *read_line(void)
{
char *line = NULL;
size_t bufsize = 0;

getline(&line, &bufsize, stdin);

return (line);
}

/**
 * parse_line - Parse a line into individual arguments.
 * @line: The input line to parse.
 *
 * Return: An array of strings representing the arguments.
 */
char **parse_line(char *line)
{
char **args;
char *token;
int i = 0;

args = malloc(64 * sizeof(char *));
if (!args)
{
perror("malloc error");
exit(EXIT_FAILURE);
}

token = strtok(line, " \t\r\n\a");
while (token != NULL)
{
args[i] = token;
i++;
token = strtok(NULL, " \t\r\n\a");
}
args[i] = NULL;
return (args);
}

/**
 * execute_external_command - Execute a command
 * with its arguments.
 * @args: An array of strings representing the
 * command and its arguments.
 *
 * Return: 1 to continue the shell loop.
 */
int execute_external_command(char **args)
{
pid_t pid;
int i, status;

pid = fork();
if (pid == 0)
{
if (execvp(args[0], args) == -1)
{
perror("shell");
}
exit(EXIT_FAILURE);
}
else if (pid < 0)
{
perror("shell");
}
else
{
waitpid(pid, &status, 0);
for (i = 0; args[i] != NULL; i++)
{
free(args[i]);
}
}

return (1);
}

/**
 * execute_builtin_or_default - Execute a built-in
 * command or a default command.
 * @args: An array of strings representing the
 * command and its arguments.
 *
 * Return: 1 to continue the shell loop if a built-in command is
 * executed, 0 otherwise.
 */
int execute_builtin_or_default(char **args)
{
if (handle_builtin_commands(args) == 0)
{
return (1);
}
else
{
fprintf(stderr, "shell: command not found: %s\n", args[0]);
return (0);
}
}

/**
 * execute_command - Execute a command with its arguments.
 * @args: An array of strings representing the command and
 * its arguments.
 *
 * Return: 1 to continue the shell loop if a command is executed,
 * 0 if the command is "exit".
 */
int execute_command(char **args)
{
if (access(args[0], X_OK) == 0)
{
return (execute_external_command(args));
}
else if (strcmp(args[0], "exit") == 0)
{
return (0);
}
else
{
return (execute_builtin_or_default(args));
}
}
