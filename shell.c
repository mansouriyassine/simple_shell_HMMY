#include <stdio.h>
#include <stdlib.h>

/**
 * main - Simple shell program that
 * displays a prompt and echoes user input
 *
 * Return: Always 0
 */
int main(void)
{
char *line = NULL;
size_t bufsize = 0;

while (1)
{
printf("#cisfun$ ");
getline(&line, &bufsize, stdin);
printf("You entered: %s", line);
}

free(line);
return (0);
}
