#include "shell.h"
#include "helpers.h"

int main(void)
{
char *line;
char **args;
int status;

do
{
printf("#cisfun$ ");
        
line = read_line();

args = parse_line(line);

status = execute_command(args);

free(line);
free(args);

}
while (status);

return (EXIT_SUCCESS);
}
