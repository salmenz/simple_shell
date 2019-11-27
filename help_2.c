#include "shell.h"
/**
 * helpHelp - prints the help... help...
 */
void helpHelp(void)
{
	_putstring("help: help [PATTERN ...]\n\n");

	_putstring("  Display information about builtin commands.\n\n");

	_putstring("  Displays brief summaries of builtin commands. If\n");
	_putstring("  PATTERN is specified, gives detailed help on all\n");
	_putstring("  commands matching PATTERN, otherwise the list of help\n");
	_putstring("  topics is printed.\n\n");

	_putstring("  Arguments:\n");
	_putstring("    PATTERN: Pattern specifiying a help topic\n\n");

	_putstring("  Exit Status:\n");
	_putstring("    Returns success unless PATTERN is not found or an\n");
	_putstring("    invalid option is given.\n");
}
/**
 * helpAlias - prints the alias help
 */
void helpAlias(void)
{
	_putstring("alias: alias [name[=value] ... ]\n\n");

	_putstring("  Define or display aliases.\n\n");

	_putstring("  Without arguments, `alias' prints the list of aliases\n");
	_putstring("  in the reusable form `alias NAME=VALUE' on standard\n");
	_putstring("  output. Otherwise, an alias is defined for each NAME\n");
	_putstring("  whose VALUE is given. A trailing space in VALUE\n");
	_putstring("  causes the next word to be checked for alias\n");
	_putstring("  substitution when the alias is expanded.\n\n");

	_putstring("  Exit Status:\n");
	_putstring("    alias returns true unless a NAME is supplied for\n");
	_putstring("    which no alias has been defined.\n");
}
/**
 * helpHistory - prints the history help
 */
void helpHistory(void)
{
	_putstring("history: history\n\n");

	_putstring("  Display the history list with line numbers.\n\n");

	_putstring("  Exit Status:\n");
	_putstring("    Returns success unless an invalid option is given\n");
	_putstring("    or an error occurs.\n");

}
