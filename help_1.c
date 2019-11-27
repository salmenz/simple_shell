#include "shell.h"
/**
 * helpExit - prints the exit help page.
 */
void helpExit(void)
{
	_putstring("exit: exit [n]\n\n");

	_putstring("  Exit the shell.\n\n");

	_putstring("  Exits the shell with a status of N. If N is omitted,\n");
	_putstring("  the exit status is that of the last command executed\n");
}
/**
 * helpEnv - prints the env help page.
 */
void helpEnv(void)
{
	_putstring("env: env  [-] [NAME=VALUE]... [COMMAND [ARG]...]\n\n");

	_putstring("  Prints out the current environment\n\n");

	_putstring("  Exit Status:\n");
	_putstring("  Returns success unless an invalid option is given\n");
	_putstring("  or an error occurs.\n");
}

/**
 * helpSetEnv - prints the setenv help page
 */
void helpSetEnv(void)
{
	_putstring("setenv: setenv [VARIABLE] [VALUE]/\n\n");

	_putstring("  The setenv() built-in adds the variable name to the\n");
	_putstring("  environment with the value value, if name does not\n");
	_putstring("  already exist. If name does exist in the environment\n");
	_putstring("  , then its value is changed to value if overwrite is\n");
	_putstring("  nonzero; if overwrite is zero, then the value of name\n");
	_putstring("  is not changed. This function makes copies of the\n");
	_putstring("  strings pointed to by name and value.\n\n");

	_putstring("  VARIABLE:\n");
	_putstring("    VARIABLE: the name of the variable to be set\n");
	_putstring("    VALUE: the value of the variable as either a single\n");
	_putstring("           word or a quoted string\n\n");

	_putstring("  Exit Status:\n");
	_putstring("    The setenv builtin returns zero on success, or -1\n");
	_putstring("    on error, with errno set to indicate the cause of\n");
	_putstring("    the error.\n");
}
/**
 * helpUnsetEnv - prints the unsetenv help page
 */
void helpUnsetEnv(void)
{
	_putstring("unsetenv: unsetenv [VARIABLE]\n\n");

	_putstring("  The unsetenv() built-in deletes the variable name\n");
	_putstring("  from the environment. If name does not exist in the\n");
	_putstring("  environment, then the functionsucceeds, and the\n");
	_putstring("  environment is unchanged.\n\n");

	_putstring("  VARIABLE:\n");
	_putstring("    VARIABLE: the name of the variable to be set]\n\n");

	_putstring("  Exit Status:\n");
	_putstring("    The unsetenv builtin returns 1 on success, or -1 on\n");
	_putstring("    error, with errno set to indicate the cause of the\n");
	_putstring("    error.\n");
}
/**
 *helpCD - prints the cd help page
 */
void helpCD(void)
{
	_putstring("help: help [PATTERN ...]\n\n");

	_putstring("  Display information about builtin commands. Displays\n");
	_putstring("  brief summaries of builtin commands. If PATTERN is\n");
	_putstring("  specified, gives detailed help on all commands\n");
	_putstring("  matching PATTERN, otherwise the list of help topics\n");
	_putstring("  is printed.\n\n");

	_putstring("  Arguments:\n");
	_putstring("    PATTERN: Pattern specifiying a help topic\n\n");

	_putstring("  Exit Status:\n");
	_putstring("    Returns success unless PATTERN is not found or an\n");
	_putstring("    invalid option is given.\n");
}
