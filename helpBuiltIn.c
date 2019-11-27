#include "shell.h"
/**
 * helpBuiltIn - finds the desired help page of the builtin
 * @file: a string of the desired help page
 *
 * Return: 1 if page found and -1 if no page is found
 */
int helpBuiltIn(char *file)
{
	if (file == NULL || file[0] == '\0')
	{
		_putstring("Select a built-in: alias, cd, env, exit,");
		_putstring(" help, history, setenv, unsetenv\n");
		return (-1);
	}
	if (_strcmp(file, "exit") == 0)
		helpExit();
	else if (_strcmp(file, "env") == 0)
		helpEnv();
	else if (_strcmp(file, "setenv") == 0)
		helpSetEnv();
	else if	(_strcmp(file, "unsetenv") == 0)
		helpUnsetEnv();
	else if (_strcmp(file, "cd") == 0)
		helpCD();
	else if (_strcmp(file, "help") == 0)
		helpHelp();
	else if (_strcmp(file, "alias") == 0)
		helpAlias();
	else if (_strcmp(file, "history") == 0)
		helpHistory();
	else
	{
		_putstring("Not a built-in of simple_shell.\n");
		return (-1);
	}
	return (1);
}
