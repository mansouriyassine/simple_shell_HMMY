#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * shell_main - Entry point for the simple shell program
 *
 * This function implements the main logic of the simple shell.
 * It reads user input, forks processes, and executes commands.
 *
 * Return: Always returns 0.
 */
int shell_main(void)
{
char *line = NULL;
size_t bufsize = 0;

while (1)
{
pid_t child_pid;
printf("#cisfun$ ");
getline(&line, &bufsize, stdin);

child_pid = fork();

if (child_pid == 0)
{
char *args[2];
args[0] = line;
args[1] = NULL;
execve(args[0], args, NULL);
perror("execve");
exit(EXIT_FAILURE);
}
else if (child_pid > 0)
{
wait(NULL);
}
else
{
perror("fork");
}
}

free(line);
return (0);
}
