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
char **args = malloc(64 * sizeof(char *));
char *token;
int i = 0;

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
 * execute_command - Execute a command with its arguments.
 * @args: An array of strings representing the command and its arguments.
 *
 * Return: 1 to continue the shell loop, 0 to exit the shell.
 */
int execute_command(char **args)
{
pid_t pid;
int status;

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
}
return (1);
}
