#include "shell.h"

/**
 * innerCat - 'concatenates' a string to the inside of a buffer
 * after remallocing it large and freeing old buffer.
 *
 * @buf: Buffer to insert string into.
 * @string: Null terminated string to insert.
 * @bufsize: Size of buffer.
 * @insert: Index of buffer where string is to be inserted.
 *
 * Return: returns the resized buffer.
 */
char *innerCat(char *buf, char *string, int *bufsize, int insert)
{
	char *newbuf;
	int newsize;

	newsize = *bufsize + _strlen(string);

	newbuf = mloc(newsize * sizeof(char), NULL);
	_memset(newbuf, '\0', newsize);
	_memcpy(newbuf, buf, insert);
	_memcpy(newbuf + insert, string, _strlen(string));
	_memcpy(newbuf + insert  + _strlen(string), buf + insert, *bufsize - insert);
	*bufsize = newsize;
	return (newbuf);
}

/**
 * sliceString - Cuts a substring out of a string and resizes it
 *
 * @buf: buffer to work with
 * @bufsize: size of buffer
 * @slicesize: size of the slice to be taken out
 * @index: where to slice in the buffer
 *
 * Return: Returns a resized buffer.
 */
char *sliceString(char *buf, int *bufsize, int slicesize, int index)
{
	char *newbuf;
	int newsize;

	newsize = *bufsize - slicesize;
	newbuf = mloc(newsize * sizeof(char), NULL);
	_memset(newbuf, '\0', newsize);
	_memcpy(newbuf, buf, index);
	if (buf[index + slicesize] != '\0')
	{
		_memcpy(newbuf + index, buf + index + slicesize,
			*bufsize - index - slicesize);
	}
	*bufsize = newsize;
	return (newbuf);
}
