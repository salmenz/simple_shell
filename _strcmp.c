#include "shell.h"
/**
 * _strcmp - concatenates two strings
 *
 * @s1: destination string
 *
 * @s2: source string
 *
 * Return: return a character
 */
int _strcmp(char *s1, char *s2)
{
int i = 0;
while (*(s1 + i) && *(s2 + i) && (*(s1 + i) == *(s2 + i)))
i++;
return (s1[i] - s2[i]);
}
