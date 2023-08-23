#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define TOKEN_BUFSIZE 64
#define TOKEN_DELIMITERS " \t\r\n\a"

void print_prompt()
{
printf("$ ");
}

char *read_input()
{
char *line = NULL;
size_t bufsize = 0;

getline(&line, &bufsize, stdin);
return (line);
}

char **parse_input(char *line)
{
int bufsize = TOKEN_BUFSIZE;
int position = 0;
char **tokens = malloc(bufsize * sizeof(char *));
char *token;

if (!tokens)
{
fprintf(stderr, "allocation error\n");
exit(EXIT_FAILURE);
}

token = strtok(line, TOKEN_DELIMITERS);
while (token != NULL)
{
tokens[position] = token;
position++;

if (position >= bufsize)
{
bufsize += TOKEN_BUFSIZE;
tokens = realloc(tokens, bufsize * sizeof(char *));
if (!tokens)
{
fprintf(stderr, "allocation error\n");
exit(EXIT_FAILURE);
}
}

token = strtok(NULL, TOKEN_DELIMITERS);
}
tokens[position] = NULL;
return tokens;
}

int execute(char **args)
{
pid_t pid;
int status;

pid = fork();
if (pid == 0) {
if (execvp(args[0], args) == -1)
{
perror("execvp error");
}
exit(EXIT_FAILURE);
} else if (pid < 0)
{
perror("fork error");
}
else
{
waitpid(pid, &status, WUNTRACED);
}
return (1);
}
