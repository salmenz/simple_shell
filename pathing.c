#include "shell.h"

/**
 * checkLocal - checking if local
 * @tok: tokenized input
 * @helper: helper struct
 * @args: tokenized argument list
 *
 * Return: 0 if success, 1 if fail, and 127 if no such file found
 */
int checkLocal(char *tok, helper_t *helper, char **args)
{
	struct stat st;

	if ((tok[0] == '.' && tok[1] == '/') || tok[0] == '/')
	{
		if (tok[0] == '.')
			tok = tok + 2;
		if (stat(tok, &st) == 0 &&
		    (st.st_mode & S_IXUSR) && S_ISREG(st.st_mode))
		{
			helper->lastExit = runProg(tok, args, helper);
			return (0);
		}
		else
		{
			if (tok[0] != '/')
				tok = (tok - 2);
			_putstring(tok);
			_putstring(": No such file or directory.\n");
			helper->lastExit = 127;
			return (127);
		}
	}
	return (1);
}

/**
 * checkBuiltins - checks for builtin commands matching the first inputted word
 *
 * @inp: input string from main
 * @helper: the ptr to the helper struct
 * @args: tokenized argument list
 *
 * Return: returns 0 on success, 1 on failure.
 */
int checkBuiltins(char *inp, helper_t *helper, char **args)
{
	hist_t *hist_head;

	hist_head = helper->hist_head;
	if (allstrcmp(inp, "env") == 0)
		listEnv(&helper->env);
	else if (allstrcmp(inp, "exit") == 0)
		exitBuiltin(args[1], inp, helper);
	else if (allstrcmp(inp, "setenv") == 0)
		setEnvPtr(args[1], args[2], helper->env);
	else if (allstrcmp(inp, "unsetenv") == 0)
		unsetEnv(args[1], &helper->env);
	else if (allstrcmp(inp, "history") == 0)
		print_hist(hist_head);
	else if (allstrcmp(inp, "cd") == 0)
		cdBuiltin(args, helper);
	else if (allstrcmp(inp, "help") == 0)
		helpBuiltIn(args[1]);
	else if (allstrcmp(inp, "alias") == 0)
		aliasBuiltin(args, helper);
	else if (allstrcmp(inp, "unalias") == 0)
		unAlias(args[1], &helper->alias);
	else
		return (1);

	return (0);
}

/**
 * checkPath - checks to see if a program is located in $PATH
 * if it is, will ruin the program and return 1
 *
 * @inp: input string we're working with
 * @helper: ptr to the helper struct
 * @args: tokenized argument list
 *
 * Return: returns 1 if program ran, 0 if some sort of error
 */
int checkPath(char *inp, char **args, helper_t *helper)
{
	int j, retval;
	char *temp, *path[PATHSIZE], *tok, *pathsave, *paths, *cwd;
	char colon = ':';

	temp = NULL; cwd = mloc(100, helper); getcwd(cwd, 100); retval = 0;
	if (getEnvPtr("PATH", helper->env) != NULL)
	{
		if (inp == NULL || inp[0] == '\0')
		{ free(cwd); return (-1); }
		paths = _strdup((getEnvPtr("PATH", helper->env))->value);
		tok = splitstr(paths, &colon, &pathsave);
		for (j = 0; tok != NULL; j++)
		{
			path[j] = tok;
			tok = splitstr(NULL, &colon, &pathsave);
		}
		path[j] = NULL;
		for (j = 0; path[j] != NULL; j++)
		{
			if (path[j][0] == '\0')
				temp = dir_concat(cwd, inp);
			else
				temp = dir_concat(path[j], inp);
			if (access(temp, X_OK) == 0)
			{
				helper->lastExit = runProg(temp, args, helper);
				break;
			}
			if (temp != NULL)
			{ free(temp); temp = NULL; }
		}
		if (path[j] == NULL)
			retval = 127;
	}
	free(cwd); free(paths);
	if (temp != NULL)
		free(temp);
	return (retval);
}

/**
 * freeArgs - frees a 2d array
 *
 * @args: argument array
 * @envsize: the size of the array holding the environment variables
 */
void freeArgs(char **args, int envsize)
{
	int i;

	for (i = 0; i < envsize; i++)
	{
		free(args[i]);
	}
	free(args);
}


/**
 * getArgs - creates a 2d array of arguments
 * last argument will be null, first will be main's argv[0]
 *
 * @tok: tokenized input
 * @argv: argv for main
 * @save: saveptr for arguments
 * Return: returns a 2d array
 */
char **getArgs(char *tok, char *argv[], char *save)
{
	char **args;
	char *arg;
	char delim = ' ';
	int i;

/* Need a clever way to get the number of args before allocating
 * Currently this just allocates space out for 1000 pntrs, that's... a lot?
 */
	(void) argv;
	arg = splitstr(NULL, &delim, &save);
	args = mloc(sizeof(char *) * 1000, NULL);
	args[0] = tok;
	i = 1;
	while (arg != NULL)
	{
		if (arg[0] != '\0')
			args[i++] = arg;
		arg = splitstr(NULL, &delim, &save);
	}
	args[i] = NULL;

	return (args);
}
