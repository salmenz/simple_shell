#include "shell.h"

/**
 * whitespace - squeezes whitespace from a buffer
 *
 * @buf: buffer
 * @helper: helper struct
 * Return: returns a squeez'd buffer
 */
char *whitespace(char *buf, helper_t *helper)
{
	unsigned int i;

	for (i = 0; i <= *helper->total && buf[i] != '\0'; i++)
	{
		for (i = i; buf[i] == ' '; i++)
		{
			if (i == 0 || buf[i - 1] == '\n')
				while (buf[i] == ' ')
					buf = bufferDelete(buf, helper, i, 1);
			if (i == 0 && (buf[i + 1] == ';' || buf[i + 1] == '\0' ||
				       buf[i + 1] == ' ' || buf[i + 1] == '\n'))
			{
				while (buf[i] == ' ')
					buf = bufferDelete(buf, helper, i, 1);
			}
			else if (i > 0 && buf[i] == ' '  && buf[i - 1] == ';')
				while (buf[i] == ' ')
					buf = bufferDelete(buf, helper, i, 1);
		}
	}
	return (buf);
}

/**
 * parseDollar - parses dollarsigns from a buffer
 *
 * @buf: buffer
 * @helper: helper struct
 *
 * Return: returns a parsed buffer
 */
char *parseDollar(char *buf, helper_t *helper)
{
	char *name, *newbuf;
	env_t *envname, *env;
	int i, j, k, start;

	start = 0; env = helper->env;
	for (i = 0; i < _strlen(buf); i++)
	{
		if (buf[i] == '$')
		{
			for (j = 0, start = ++i; !isDelimiter(buf[i]) && (!isWhitespace(buf[i]))
				     && buf[i] != '$' && buf[i] != '?'; i++, j++)
				;
			if (j == 0 && buf[i] == '$')
				buf = insertPid(buf, helper, start);
			if (j == 0 && buf[i] == '?')
				buf = insertLastExit(buf, helper, start);
			else if (j != 0)
			{
				name = mloc((j + 1) * (sizeof(char)), helper);
				for (k = start, j = 0; k != i; j++, k++)
					name[j] = buf[k];
				name[j] = '\0';
				envname = getEnvPtr(name, env);
				if (envname == NULL)
				{
					newbuf = sliceString(buf, helper->bufsize, _strlen(name) + 1, start - 1);
					free(helper->inphead);
					buf = newbuf;
					helper->inphead = buf;
				}
				else
					buf = insertEnvValue(buf, envname->value, helper, start, name);
				free(name);
			}
		}
		if (start != 0)
		{ i = start; start = 0; }
	}
	return (buf);
}

/**
 * insertEnvValue - helper func to insert the value of an environmental var
 *
 * @buf: buffer to insert into
 * @value: value to insert
 * @helper: helper_t struct
 * @start: where parsedollars found the name at
 * @name: variable name
 *
 * Return: returns a pointer to the buffer or NULL on failure
 */
char *insertEnvValue(char *buf, char *value,
		     helper_t *helper, int start, char *name)
{
	char *newbuf;

	newbuf = sliceString(buf, helper->bufsize, _strlen(name) + 1, start - 1);
	buf = innerCat(newbuf, value, helper->bufsize, start - 1);
	free(newbuf);
	free(helper->inphead);
	(helper->inphead) = buf;
	return (buf);
}

/**
 * insertPid - helper func to insert the last PID
 *
 * @buf: buffer to insert into
 * @helper: helper_t struct
 * @start: where parsedollars found the name at
 *
 * Return: returns a pointer to the buffer or NULL on failure
 */
char *insertPid(char *buf, helper_t *helper, int start)
{
	char *newbuf;

	newbuf = sliceString(buf, helper->bufsize, 2, start - 1);
	buf = innerCat(newbuf, helper->pid, helper->bufsize, start - 1);
	free(newbuf);
	free(helper->inphead);
	(helper->inphead) = buf;
	return (buf);
}

/**
 * insertLastExit - helper func to insert the last exit status
 *
 * @buf: buffer to insert into
 * @helper: helper_t struct
 * @start: where parsedollars found the name at
 *
 * Return: returns a pointer to the buffer or NULL on failure
 */
char *insertLastExit(char *buf, helper_t *helper, int start)
{
	char *newbuf, *name;

	name = mloc(100, helper);
	itoa(helper->lastExit, name);
	newbuf = sliceString(buf, helper->bufsize, 2, start - 1);
	buf = innerCat(newbuf, name, helper->bufsize, start - 1);
	free(newbuf);
	free(helper->inphead);
	(helper->inphead) = buf;
	free(name);
	return (buf);
}
