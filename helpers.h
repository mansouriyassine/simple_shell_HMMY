#ifndef HELPERS_H
#define HELPERS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/* Function prototypes for helper functions */
char *read_line(void);
char **parse_line(char *line);
int execute_command(char **args);

#endif /* HELPERS_H */