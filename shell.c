#include "shell.h"

/**
 * main - Entry point for the simple shell program.
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

execute_command(line);
}

free(line);
return (0);
}
