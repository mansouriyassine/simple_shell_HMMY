#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * main - Entry point for the simple shell program.
 *
 * This function implements the basic functionality of a simple shell,
 * which displays a prompt, reads user input, and executes commands.
 * It also handles the "end of file" condition (Ctrl+D).
 *
 * Return: Always 0.
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
{
printf("\n");
break;
}
else
{
perror("getline");
exit(EXIT_FAILURE);
}
}

if (line[nread - 1] == '\n')
{
line[nread - 1] = '\0';
}

printf("Executing: %s\n", line);
}

free(line);
return (0);
}
