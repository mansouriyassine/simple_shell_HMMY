#include "shell.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * main - Entry point of the simple shell program
 *
 * This function serves as the entry point for the simple shell.
 * It repeatedly prints the shell prompt, reads input, parses the input,
 * and executes the parsed arguments as a command.
 *
 * Return: Always returns 0.
 */

int main(int argc, char *argv[])
{
char *line = NULL;
char **args = NULL;
size_t bufsize = 0;
ssize_t read_bytes;

if (argc == 1)
{
while (1)
{
print_prompt();
read_bytes = getline(&line, &bufsize, stdin);
if (read_bytes == -1)
{
perror("getline");
exit(EXIT_FAILURE);
}
line[read_bytes - 1] = '\0';

args = parse_input(line);
if (args[0] != NULL)
{
execute(args);
}

free(line);
free(args);
}
}
else if (argc == 2)
{
FILE *file = fopen(argv[1], "r");
if (file == NULL)
{
perror("fopen");
exit(EXIT_FAILURE);
}

while ((read_bytes = getline(&line, &bufsize, file)) != -1)
{
line[read_bytes - 1] = '\0';
args = parse_input(line);
if (args[0] != NULL)
{
execute(args);
}
free(args);
}

free(line);
fclose(file);
}

return (0);
}
