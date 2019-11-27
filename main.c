#include "shell.h"
/**
 * main - entry point for shell program
 * loops input for a shell, splits them into appropriate actions
 *
 * @argc: argument count
 * @argv: arguments passed
 * @envp: list of environment names and their values
 *
 * Return: return values in man page
 */
int main(int argc, char *argv[], char *envp[])
{
	helper_t *helper;
	char *save, *tok, *inp, **args, *buf;
	char delim = ' ';

	helper = setupMain(argc, argv, envp);
	signal(SIGINT, sighandler);
	while (1)
	{
		while ((*helper->total) <= 0)
		{
			if (argc == 1 && helper->type == 1)
				prompt();
			buf = get_line(helper->file, helper);
		}
		inp = mloc(*helper->bufsize, helper);
		inp = _memcpy(inp, buf, (*helper->bufsize));
		(helper->inphead) = inp; (helper->bufhead) = buf;
		save = NULL; args = NULL;
		(*helper->last) = 0;
		while (inp != NULL)
		{
			countLine(buf, helper);
			inp = parseAlias(inp, helper);
			inp = parseDollar(inp, helper);
			tok = splitstr(inp, &delim, &save);
			helper->args = getArgs(tok, args, save);
			if (checkBuiltins(inp, helper, helper->args) == 1)
				if (checkLocal(inp, helper, helper->args) == 1)
				{
					helper->lastExit = checkPath(tok, helper->args, helper);
					if (helper->lastExit != 0)
					{ _putstring(tok); _putstring(": command not found.\n"); }
				}
			if (inp != NULL)
			{ free(helper->args); helper->args = NULL; }
			inp = moreLines(helper, buf, inp); save = NULL;
		}
		if (inp == NULL && (argc == 2 || helper->type == 0))
			exitBuiltin("0", NULL, helper);
	}
}

/**
 * setupMain - populates helper struct, determine if given STDIN, or File,
 * initialize the hist and env struct, grab the parent pid, and determines if
 * file in termianl or a pipe.
 * @argc: arugment count
 * @argv: arguements passed
 * @envp: list of environment names and their values
 *
 * Return: the helper struct
 */
helper_t *setupMain(int argc, char **argv, char **envp)
{
	char *pid;
	env_t *head;
	hist_t *hist_head;
	helper_t *helper;
	alias_t *alias;

	pid = _getpid();
	hist_head = NULL;
	head = NULL;
	alias = NULL;

	if (argc > 2 || argv == NULL || envp == NULL)
	{
		_putstring("Please run with no argument, or filename to run from script.");
		_exit(9);
	}

	initEnvList(envp, &head);
	hist_head = pull_hist(&hist_head, head);
	helper = initHelper(head, hist_head, pid);
	helper->alias = alias;

	if (argc == 1)
		helper->file = STDIN_FILENO;
	else if (argc == 2)
	{
		helper->file = open(argv[1], O_RDONLY);
		if (helper->file == -1)
		{
			_putstring("Error opening script file: ");
			_putstring(argv[1]);
			_putchar('\n');
			_exit(9);
		}
	}

	helper->type = getTermType(helper->file);

	return (helper);
}


/**
 * getTermType - checks if file is in terminal, or if file is has a pipe
 * @file: typically STDIN_FILENO
 *
 * Return: 1 if in terminal, 0 if pipe and -1 if fail
 */
int getTermType(int file)
{
	struct stat st;

	fstat(file, &st);
	if (S_ISCHR(st.st_mode))
	{
		return (1);
	}
	else if (S_ISFIFO(st.st_mode))
	{
		return (0);
	}
	return (-1);
}
/**
 * initHelper - fills and intialize values of the helper struct
 * @env: the head of the env linked list
 * @hist_head: the head of the hist linked list
 * @pid: the pid of the parents process
 *
 * Return: the ptr of the struct helper
 */
helper_t *initHelper(env_t *env, hist_t *hist_head, char *pid)
{
	helper_t *helper;

	helper = mloc(sizeof(helper_t), NULL);
	helper->env = env;
	helper->hist_head = hist_head;
	helper->printed = mloc(sizeof(int) * 1, NULL);
	*(helper->printed) = 0;
	helper->total = mloc(sizeof(long) * 1, NULL);
	*(helper->total) = 0;
	helper->bufsize = mloc(sizeof(int) * 1, NULL);
	*(helper->bufsize) = 1024;
	helper->last = mloc(sizeof(int) * 1, NULL);
	*(helper->last) = 0;
	helper->args = NULL;
	helper->pid = pid;
	helper->lastExit = 0;
	helper->alias = NULL;

	return (helper);
}


/**
 * runProg - runs a program by forking and running it on the child
 *
 * @name: name of program (including whole path)
 * @argv: 2d array of arguments, either from main, or from getArgs
 * @helper: ptr to the helper struct
 *
 * Return: returns -1 on failure, or the exit status of the child
 */
int runProg(char *name, char *argv[], helper_t *helper)
{
	pid_t cpid;
	int cstatus, envsize;
	char **envs;

	envs = buildEnv(helper->env, &envsize);
	cpid = fork();
	if (cpid == -1) /* if fork returns -1, it failed */
	{
		_putstring("Failure to fork!");
		exit(9);
	}
	else if (cpid == 0) /* if fork return is 0, we are the child proc */
	{
		execve(name, argv, envs);
		_putstring("Attempted to run unknown command: ");
		_putstring(name);
		_putchar('\n');
		exit(-1);
	}
	else /* if neither are true, we're in the parent */
	{
		wait(&cstatus); /* wait til we get back */
		freeArgs(envs, envsize);
		return (cstatus); /* now return the child's exit status */
	}

}
