#include "helpers.h"

char *read_line(void)
{
char *line = NULL;
size_t bufsize = 0;

getline(&line, &bufsize, stdin);

return (line);
}

char **parse_line(char *line)
{
char **args = malloc(64 * sizeof(char*));
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

int execute_command(char **args)
{
pid_t pid, wpid;
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
do
{
wpid = waitpid(pid, &status, WUNTRACED);
} while
(!WIFEXITED(status) && !WIFSIGNALED(status));
}
return (1);
}
