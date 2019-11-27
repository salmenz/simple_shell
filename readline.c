#include "shell.h"
/**
 * readline - readline function
 *
 * Return: char
 */
char *readline(void)
{
int bufsize = BUFSIZE;
int idx = 0;
char *buff = malloc(sizeof(char) * bufsize);
int c;
if (!buff)
{
perror("ysh");
exit(EXIT_FAILURE);
}
while (1)
{
signal(SIGINT, sigintHandler);
c = getchar();
if (c == EOF)
{
_putchar('\n');
exit(0);
}
else if (c == '\n')
{
buff[idx] = '\0';
return (buff);
}
else
{
buff[idx] = c;
}
idx++;
if (idx >= bufsize)
{
bufsize += BUFSIZE;
buff = realloc(buff, bufsize);
if (!buff)
{
perror("ysh");
exit(EXIT_FAILURE);
}
}
}
}
