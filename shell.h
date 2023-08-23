#ifndef SHELL_H
#define SHELL_H

void print_prompt(void);
char *read_input();
char **parse_input(char *line);
int execute(char **args);

#endif
