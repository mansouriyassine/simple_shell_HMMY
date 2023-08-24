#include "shell.h"

/**
 * execute_command - Executes a command entered by the user.
 * @command: The command to be executed.
 *
 * This function creates a child process using fork(), and in the child
 * process, it uses execve() to execute the specified command. If execve()
 * fails, an error message is printed. The parent process waits for the
 * child process to complete using waitpid().
 */
void execute_command(char *command)
{
pid_t child_pid;
int status;

child_pid = fork();

if (child_pid == -1)
{
perror("fork");
return;
}
else if (child_pid == 0)
{
char **args = malloc(sizeof(char *) * 2);
if (args == NULL)
{
perror("malloc");
exit(EXIT_FAILURE);
}

args[0] = command;
args[1] = NULL;

execve(args[0], args, NULL);

perror("execve");
exit(EXIT_FAILURE);
}
else
{
waitpid(child_pid, &status, 0);
}
}
