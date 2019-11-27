#include "shell.h"

/**
 * sighandler - the signal handler
 * @signum: a signal number corresponding to the signal
 */
void sighandler(int signum)
{
	(void) signum;
	write(0, "\n", 1);
	prompt();
}
