#include "shell.h"
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
char *line;
char **args;

while (1)
{
print_prompt();
line = read_input();
args = parse_input(line);
execute(args);
free(line);
free(args);
}

return (0);
}
