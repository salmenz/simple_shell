#include "shell.h"


/**
 * aliasBuiltin - determines what to do with alias input
 *
 * @args: 2d array of arguments
 * @helper: helper_t struct
 */
void aliasBuiltin(char **args, helper_t *helper)
{
	int i;

	if (args[1] == NULL)
	{
		listAlias(helper);
		return;
	}
	for (i = 0; args[1][i] != '\0'; i++)
	{
		if (args[1][i] == '=')
		{
			addAlias(args, helper, &helper->alias);
			return;
		}
	}
	if (getAlias(args[1], helper->alias) == NULL)
		_putstring("No such alias to display.\n");
}


/**
 * listAlias - lists available aliases, or lets you know that there aren't any
 *
 * @helper: helper_t struct
 * Return: Returns 1
 */
int listAlias(helper_t *helper)
{
	alias_t *walk;

	walk = helper->alias;
	if (walk == NULL)
	{
		_putstring("No aliases.\n");
		return (1);
	}
	while (walk != NULL)
	{
		_putstring("alias ");
		_putstring(walk->name);
		_putchar('=');
		_putchar('\'');
		_putstring(walk->value);
		_putchar('\'');
		_putchar('\n');
		walk = walk->next;
	}
	return (1);

}

/**
 * addAlias - adds an alias
 * does not check to see if one already exists (check beforehand plz)
 *
 * @args: argument 2d array
 * @helper: helper_t struct
 * @head: head of alias_t list
 * Return: returns a pointer to the new node
 */
alias_t *addAlias(char **args, helper_t *helper, alias_t **head)
{
	alias_t *newnode, *tempnode;
	char *value, *save, *name;
	char *space = " ";
	int i;

	name = splitstr(args[1], "=", &save);
	if (getAlias(name, helper->alias) != NULL)
		unAlias(name, &helper->alias);
	value = mloc(1000, helper);
	_memset(value, '\0', 1000);
	_strcat(value, save);
	_strcat(value, space);
	for (i = 2; args[i] != NULL; i++)
	{
		_strcat(value, args[i]);
		_strcat(value, space);
	}
	value[_strlen(value) - 1] = '\0';
	if (head == NULL || name == NULL || value == NULL)
		return (NULL);
	newnode = mloc(sizeof(alias_t), NULL);
	if (newnode == NULL)
		return (NULL);
	newnode->name = _strdup(name);
	newnode->value = value;
	if (*head == NULL)
	{
		newnode->next = *head;
		*head = newnode;
	}
	else
	{
		newnode->next = NULL;
		tempnode = *head;
		while (tempnode->next != NULL)
			tempnode = tempnode->next;
		tempnode->next = newnode;
	}
	return (newnode);
}

/**
 * getAlias - checks to see if there's an alias under that name
 *
 * @name: name of environment variable to search for
 * @head: the head of the alias linked list
 * Return: returns a pointer to the alias_t struct
 */
alias_t *getAlias(char *name, alias_t *head)
{
	alias_t *alist;

	alist = head;
	while (alist != NULL)
	{
		if (allstrcmp(name, alist->name) == 0)
			return (alist);
		alist = alist->next;
	}
	return (NULL);
}

/**
 * free_alist - frees a alias_t linked list
 * @head: head of alias_t linked list
 */
void free_alist(alias_t *head)
{
	alias_t *temp;

	temp = head;
	while (head != NULL)
	{
		temp = head;
		head = head->next;
		free(temp->name);
		free(temp->value);
		free(temp);
	}
	free(head);
}

