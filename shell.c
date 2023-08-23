#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_ARGS 10

/**
 * execute_command_with_args - Executes a command with arguments using execve.
 * @command: The command to execute.
 * @args: An array of strings representing the command and its arguments.
 */
void execute_command_with_args(char *command, char *args[])
{
char *path = "/bin/";
char *full_path = (char *)malloc(strlen(path) + strlen(command) + 1);

if (full_path == NULL)
{
perror("malloc");
exit(1);
}

strcpy(full_path, path);
strcat(full_path, command);

if (execve(full_path, args, NULL) == -1)
{
perror("execve");
}

free(full_path);
}

/**
 * parse_input - Parses user input into a command and arguments array.
 * @line: The input line.
 * @command: Pointer to store the parsed command.
 * @args: Pointer to store the parsed arguments.
 */
void parse_input(char *line, char **command, char **args)
{
char *token;
int arg_count = 1;

token = strtok(line, " ");
*command = token;

while (token != NULL)
{
token = strtok(NULL, " ");
args[arg_count++] = token;
}

args[arg_count] = NULL;
}

/**
 * main - Entry point of the simple shell program.
 *
 * This function initializes the shell and enters an infinite loop to read
 * user commands and execute them using the execve system call.
 *
 * Return: Always returns 0 to indicate successful execution.
 */
int main(void)
{
char *line = NULL;
size_t len = 0;
ssize_t nread;

while (1)
{
char *command;
char *args[MAX_ARGS];

printf("#cisfun$ ");
nread = getline(&line, &len, stdin);

if (nread == -1)
{
if (feof(stdin))
break;
perror("getline");
continue;
}

if (line[nread - 1] == '\n')
line[nread - 1] = '\0';

parse_input(line, &command, args);

execute_command_with_args(command, args);
}

free(line);
return (0);
}
