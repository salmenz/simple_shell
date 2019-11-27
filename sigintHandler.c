#include "shell.h"
/**
 * sigintHandler - sigintHandler function
 * @sig_num: int
 *
 */
void sigintHandler(int sig_num __attribute__((unused)))
{
fflush(stdout);
}
