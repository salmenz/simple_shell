#include "shell.h"


/**
 * parseAlias - parses aliases!
 *
 * @helper: helper_t struct
 * @buf: buffer to parse
 * Return: returns the new buffer!
 */
char *parseAlias(char *buf, helper_t *helper)
{
	alias_t *alias;
	char *newbuf;
	int newsize;
	char *name;
	int i;

	name = malloc(*helper->bufsize);
	i = 0;
	while (buf[i] != ' ' && buf[i] != ';' && buf[i] != '\0')
	{
		name[i] = buf[i];
		i++;
	}
	name[i] = '\0';
	alias = getAlias(name, helper->alias);
	if (alias == NULL)
	{
		free(name);
		return (buf);
	}
	newsize = _strlen(alias->value) + *helper->bufsize;
	newbuf = mloc(newsize, helper);
	_memset(newbuf, '\0', newsize);
	newbuf = _memcpy(newbuf, alias->value, _strlen(alias->value));
	_memcpy(newbuf + _strlen(alias->value) + 1, buf + _strlen(name),
		(*helper->bufsize) - (_strlen(name) + 10));
	newbuf[_strlen(alias->value)] = ' ';
	free(helper->inphead);
	free(name);
	helper->inphead = newbuf;
	return (newbuf);
}
