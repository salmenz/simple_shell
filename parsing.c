#include "shell.h"

/**
 * parseComments - removes comments from the buffer
 *
 * @buf: buffer
 * @helper: helper_t struct
 *
 * Return: returns parsed buffer
 */
char *parseComments(char *buf, helper_t *helper)
{
	int i;

	for (i = 0; i < _strlen(buf); i++)
	{
		if (buf[i] == '#')
		{
			if (i == 0 || isDelimiter(buf[i - 1]) || buf[i - 1] == ' ')
			{
				while (buf[i] != '\0' && _strlen(buf) > i)
				{
					buf = sliceString(buf, helper->bufsize, 1, i);
				}
			}
		}
	}
	return (buf);
}

/**
 * bufferDelete - func to delete chunks of the buffer using slicestring
 *
 * @buf: buffer
 * @helper: helper struct
 * @index: index to delete from
 * @times: times to delete
 *
 * Return: returns the modified buffer
 */
char *bufferDelete(char *buf, helper_t *helper, int index, int times)
{
	char *newbuf;

	newbuf = sliceString(buf, helper->bufsize, times, index);
	free(buf);
	buf = newbuf;

	return (buf);
}


/**
 * isDelimiter - checks to see if a character is a delimiter
 *
 * @c: char to check
 * Return: returns 1 if it is, 0 if it isn't a delim
 */
int isDelimiter(char c)
{
	if (c == ';' || c == '\n' || c == '\0')
		return (1);
	else
		return (0);
}

/**
 * isWhitespace - checks to see if a char is whitespace
 *
 * @c: char to check
 * Return: returns 1 if it is, 0 if it isn't whitespace
 */
int isWhitespace(char c)
{
	if (c == ' ' || c == '\n' || c == '\t')
		return (1);
	else
		return (0);
}

/**
 * _getpid - gets the PID of the currently running process
 * Return: returns a string containing the PID
 */
char *_getpid(void)
{
	pid_t pid;
	char *cpid, *dir, *buf, *save, *tok, *newbuf;
	int file, status, readval;

	pid = fork();
	if (pid > 0)
	{
		cpid = mloc(sizeof(long) * sizeof(char), NULL);
		cpid[0] = '\0';
		dir = mloc(100, NULL);
		dir[0] = '\0';
		itoa(pid, cpid);
		_strcat(dir, "/proc/");
		_strcat(dir, cpid);
		_strcat(dir, "/stat");
		file = open(dir, O_RDONLY);
		buf = mloc(1024, NULL);
		readval = read(file, buf, 1024);
		if (readval < 0)
		{
			perror("Error reading from /proc/: ");
			return (NULL);
		}
		tok = splitstr(buf, " ", &save);
		tok = splitstr(NULL, " ", &save);
		tok = splitstr(NULL, " ", &save);
		tok = splitstr(NULL, " ", &save);
		wait(&status);
	}
	else
	{
		_exit(0);
	}
	free(dir);
	free(cpid);
	newbuf = mloc(_strlen(tok) + 1, NULL);
	_memcpy(newbuf, tok, _strlen(tok) + 1);
	free(buf);
	close(file);
	return (newbuf);
}
