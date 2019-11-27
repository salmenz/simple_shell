#include "shell.h"
/**
 * main - Shell in c.
 * Return: EXIT_SUCCESS
*/
int main(void)
{
char *cmdline;
char **args;
int exit;
do {
_puts("#cisfun$ ");
cmdline = readline();
args = splitline(cmdline, LINE_DELIM);
exit = execute(args);
free(cmdline);
free(args);
} while (exit);
return (EXIT_SUCCESS);
}
