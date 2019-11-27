#include "shell.h"
/**
 * _puts - writes the string
 * @str: The character to print
 */
void _puts(char *str)
{
while (*str)
_putchar(*str++);
}
