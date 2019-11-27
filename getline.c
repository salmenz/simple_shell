 #include "shell.h"


/**
 * get_line - gets a line from given file
 *
 * @file: file passed
 * @helper: helper_t helper struct
 *
 * Return: returns a pointer to the new buff
 */
char *get_line(int file, helper_t *helper)
{
	char *newbuf, *readbuf, *buf;
	long readval;

	buf = mloc(sizeof(char) * (*helper->bufsize), helper);
	(helper->bufhead) = buf;
	_memset(buf, '\0', (*helper->bufsize));
	readval = read(file, buf, *helper->bufsize);
	if (readval == -1)
	{ perror("Read error:"); exitBuiltin("99", buf, helper); }
	(*helper->total) = readval;
	if (readval <= 0)
	{
		if (helper->type == 1)
			_putchar('\n');
		exitBuiltin("0", buf, helper);
	}
	while (readval >= 1024)
	{
		readbuf = mloc(1024, helper);
		readval = read(file, readbuf, 1024);
		newbuf = mloc((*helper->bufsize) + 1024, helper);
		_memset(newbuf, '\0', (*helper->bufsize) + 1024);
		newbuf = _memcpy(newbuf, buf, (*helper->bufsize));
		_memcpy(newbuf + (*helper->bufsize), readbuf, 1024);
		free(buf); buf = newbuf; free(readbuf);
		(*helper->total) += readval; (*helper->bufsize) += 1024;
	}
	buf[(*helper->total - 1)] = '\0';
	if (buf[0] != '\0')
		add_hist((*helper->total + 1), &helper->hist_head, buf);
	buf = whitespace(buf, helper);
	buf = parseComments(buf, helper);
	countBuf(buf, helper);
	if (*helper->total <= 0)
	{
		free(buf);
		return (buf);
	}
	buf = parseDelimiters(buf, helper);
	helper->bufhead = buf;
	return (buf);
}
/**
 * parseDelimiters - replace delimiters with '\0'
 * @buf: the buffer
 * @helper: the helper struct
 *
 * Return: the buffer
 */
char *parseDelimiters(char *buf, helper_t *helper)
{
	int i, j;

	for (i = 0, j = 0; i < *helper->total; i++)
	{
		if (buf[i] == EOF)
		{
			buf[i] = '\0';
			j++;
		}
		if (buf[i] == ';')
		{
			buf[i] = '\0';
			j++;
		}
		else if (buf[i] == '\n')
		{
			buf[i] = '\0';
			j++;
		}
	}
	(helper->linecount) = j + 1;
	return (buf);
}
/**
 * countBuf - count and save the length of buf after parse comments,
 * parse the dollar and removed excess white space.
 * @buf: buffer after it's been expanded
 * @helper: the helper struct
 * Return: returns the buffer, or NULL
 */
void *countBuf(char *buf, helper_t *helper)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
		;
	(*helper->total) = i;
	(*helper->printed) = 0;
	if (i == 0)
		return (NULL);
	return (buf);
}
/**
 * countLine - counts the len of a line after delimiter have been
 * replaced with '\0'
 * @buf: buffer
 * @helper: the helper struct
 */
void countLine(char *buf, helper_t *helper)
{
	int i;

	i = *helper->last;
	for (i = i; buf[i] != '\0'; i++)
		;
	if (buf[i + 1] == '\0' && i < *helper->total)
	{
		helper->linecount -= 1;
	}
	while (buf[i + 1] == '\0' && i < *helper->total)
	{
		i++;
	}
	*(helper->printed) += i + 1;
	*(helper->last) = i + 1;
	(helper->bufnext) = (helper->bufhead) + (*helper->last);
}


/**
 * moreLines - helper func for getline. Ran to check to see if there is
 * unprinted lines left in the buffer.
 *
 * @helper: helper struct
 * @buf: buffer
 * @inp: input line
 * Return: Returns a pointer to the next line, or NULL if there are no more
 */
char *moreLines(helper_t *helper, char *buf, char *inp)
{
	(void) buf; /*need to remove buf from the prototype */
	(helper->linecount)--;
	if (helper->linecount == 0)
	{
		free(helper->inphead);
		free(helper->bufhead);
		(*helper->printed) = 0;
		(*helper->total) = 0;
		return (NULL);
	}
	inp = helper->bufnext;
	if (*inp == '\0')
		inp++;
	return (inp);
}
