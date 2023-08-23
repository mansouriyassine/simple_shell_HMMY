#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * execute_command - Executes a command using execve.
 * @command: The command to execute.
 */
void execute_command(char *command)
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

if (execve(full_path, &command, NULL) == -1)
{
perror("execve");
}

free(full_path);
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

execute_command(line);
}

free(line);
return (0);
}
