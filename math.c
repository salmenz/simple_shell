#include "shell.h"

/**
 * itoa - convert integer @n to string @s
 * @n: integer number
 * @s: character array
 *
 * Return: returns int for position of format
 */
int itoa(int n, char *s)
{
	int i = 0;

	if (n / 10 != 0)
		i = itoa(n / 10, s);
	else if (n < 0)
		s[i++] = '-';

	s[i++] = _abs(n % 10) + '0';
	s[i] = '\0';

	return (i);
}


/**
 * _abs - return absolute value of @num
 * @num: integer number
 *
 * Return: absolute value of @num
 */
int _abs(int num)
{
	if (num < 0)
		return (num * -1);
	else
		return (num);
}
