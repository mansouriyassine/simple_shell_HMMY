#include "shell.h"
#include "helpers.h"

/**
 * sigint_handler - Handle the SIGINT signal (Ctrl+C).
 * @sig: The signal number.
 */
void sigint_handler(int sig)
{
(void)sig;
write(STDOUT_FILENO, "\n#cisfun$ ", 10);
}

/**
 * main - Entry point for the simple shell program.
 *
 * Return: EXIT_SUCCESS on successful completion.
 */
int main(void)
{
char *line;
char **args;
int status;

signal(SIGINT, sigint_handler);
do {
printf("#cisfun$ ");
line = custom_read_line();
args = parse_line(line);

status = execute_command(args);

free(line);
free(args);

} while (status);

return (EXIT_SUCCESS);
}
