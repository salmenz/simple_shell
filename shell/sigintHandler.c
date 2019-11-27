#include "shell.h"
/**
 * sigintHandler - sigintHandler function
 * @sig_num: int
 *
 */
void sigintHandler(int sig_num __attribute__((unused)))
{
_putchar('\n');
_puts("#SYshell$ ");
fflush(stdout);
}
