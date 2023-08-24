#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *custom_read_line(void);
char **parse_line(char *line);
int execute_command(char **args);

#endif /* SHELL_H */
