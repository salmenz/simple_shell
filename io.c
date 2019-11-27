#include "shell.h"

/**
 * prompt - prints a prompt
 */
void prompt(void)
{
	char *cwd;

	cwd = getcwd(NULL, 100);
	_putstring(cwd);
	_putchar('$');
	_putchar(' ');
	free(cwd);
}

/**
 * _putstring - prints a string to stdout, without a newline
 *
 * @str: string to print
 * Return: void
 */
void _putstring(char *str)
{
	int i;

	if (str == NULL)
		return;
	i = 0;
	while (str[i] != '\0')
		_putchar(str[i++]);
}

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	return (write(1, &c, 1));
}
/**
 * _putint - prints out an int
 * @i: an int
 * @flag: set flag to 0. To account for i == 0
 *
 */
void _putint(int i, int flag)
{
	if (i != 0)
	{
		_putint(i / 10, 1);
		_putchar(i % 10 + '0');
	}
	else if (i == 0 && flag == 0)
	{
		_putchar('0');
	}
}
