#include "shell.h"

/**
 * cdBuiltin - function to execute the builtin CD command
 * sets the pwd and oldpwd environmental variables appropriately
 *
 * @args: tokenized arguments
 * @helper: ptr to the helper struct
 * Return: 1 on success, 0 on failure
 */
int cdBuiltin(char **args, helper_t *helper)
{
	char *oldcwd, *home, *tok;

	tok = args[1];
	oldcwd = getcwd(NULL, 100);
	home = (getEnvPtr("HOME", helper->env))->value;

	if (tok == NULL) /*If no argument, we want to go HOME */
	{
		chdir(home);
		setEnvPtr("PWD", home, helper->env);
		setEnvPtr("OLDPWD", oldcwd, helper->env);
		free(oldcwd);
		return (1); /*return 1, success*/
	}
	if (tok[0] == '-' && tok[1] == '\0') /*if we do cd -*/
	{
		if (getEnvPtr("OLDPWD", helper->env) == NULL)
		{
			_putstring("cd: OLDPWD not set.\n");
			free(oldcwd);
			return (0);
		}
		tok = (getEnvPtr("OLDPWD", helper->env))->value;
		_putstring(tok);
		_putchar(10);
	}
	if (chdir(tok) != -1)
	{
		setEnvPtr("PWD", tok, helper->env);
		setEnvPtr("OLDPWD", oldcwd, helper->env);
		free(oldcwd);
		return (1);
	}
	_putstring("cd: Invalid folder.\n");
	free(oldcwd);
	return (0);
}

/**
 * exitBuiltin - executes the exit builtin and exits clean
 *
 * @tok: argument for exitBuiltin
 * @inp: input (to free)
 * @helper: helper struct
 */
void exitBuiltin(char *tok, char *inp, helper_t *helper)
{
	int i;

	if (tok != NULL)
		i = _atoi(tok);
	else
		i = 0;
	push_hist(helper->hist_head, helper->env);
	if (inp != NULL)
	{
		if (inp != helper->bufhead)
			free(helper->bufhead);
		free(inp);
	}
	clear_hist(&(helper->hist_head));
	free_list(helper->env);
	free(helper->printed);
	free(helper->total);
	free(helper->last);
	free(helper->bufsize);
	free(helper->pid);
	if (helper->alias != NULL)
		free_alist(helper->alias);
	if (helper->args != NULL)
		free(helper->args);
	free(helper);
	_exit(i & 255);
}

/**
 * listEnv - prints the list of environ variables
 *
 * @environ: environ_t head
 * Return: Returns -1 on failure or 1 on success
 */
int listEnv(env_t **environ)
{
	env_t *walk;

	walk = *environ;
	if (walk == NULL)
	{
		_putstring("Issue printing environment variables!");
		return (-1);
	}
	while (walk != NULL)
	{
		_putstring(walk->name);
		_putchar('=');
		_putstring(walk->value);
		_putchar('\n');
		walk = walk->next;
	}
	return (1);
}

/**
 * unsetEnv - removes an environmental variable
 *
 * @head: head of environment list
 * @name: name of environmental variable to remove
 * Return: returns 1 on success, -1 on failure
 */
int unsetEnv(char *name, env_t **head)
{
	int i;
	env_t *temp, *last;

	temp = *head;
	if (name == NULL)
	{
		_putstring("Invalid name.\n");
		return (-1);
	}
	i = 0;
	while (temp != NULL)
	{
		if (_strcmp(name, temp->name) == 0)
		{
			if (i == 0)
			{
				*head = temp->next;
				free(temp->name);
				free(temp->value);
				free(temp);
			}
			else
			{
				last->next = temp->next;
				free(temp->name);
				free(temp->value);
				free(temp);
			}
			return (1);
		}
		last = temp;
		temp = temp->next;
		i++;
	}
	_putstring("No such environmental variable.\n");
	return (-1);
}


/**
 * setEnvPtr - sets an environment variable to a new value
 * creates a new one if none found
 *
 * @envname: Name to variable to set/create
 * @value: Value for environmental variable
 * @head: head of env_t linked list
 * Return: returns a pointer to the new environmental variable
 *
 * TODO: need to error check the malloc'd returns and return null on fail
 */
env_t *setEnvPtr(char *envname, char *value, env_t *head)
{
	env_t *environ;
	char *newvalue;

	environ = head;
	if (envname == NULL)
	{
		_putstring("Invalid environment variable name.\n");
		return (NULL);
	}
	if (value == NULL)
	{
		_putstring("Invalid value for enviroment variable.\n");
		return (NULL);
	}
	environ = getEnvPtr(envname, head);
	if (environ != NULL)
	{
		newvalue = _strdup(value);
		free(environ->value);
		environ->value = newvalue;
		return (environ);
	}
	return (addEnv(&head, envname, value)); /*return the result*/
}
