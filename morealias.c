#include "shell.h"

/**
 * unAlias - removes an alias
 *
 * @head: head of alist
 * @name: name of alias
 * Return: returns 1 on success, -1 on failure
 */
int unAlias(char *name, alias_t **head)
{
	int i;
	alias_t *temp, *last;

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
	_putstring("No such alias.\n");
	return (-1);
}
