#include "shell.h"
/**
 * splitline - splitline function
 * @line: string
 * @del: string
 * Return: char
 */
char **splitline(char *line, char *del)
{
int bufsize = BUFSIZE, i = 0;
char **arr = malloc(BUFSIZE * sizeof(char *));
char *token, **tokens_backup;
if (!arr)
{
perror("ysh");
exit(EXIT_FAILURE);
}
token = strtok(line, del);
while (token != NULL)
{
arr[i] = token;
i++;
if (i >= bufsize)
{
bufsize += BUFSIZE;
tokens_backup = arr;
arr = realloc(arr, BUFSIZE * sizeof(char *));
if (!arr)
{
free(tokens_backup);
perror("ysh");
exit(EXIT_FAILURE);
}
}
token = strtok(NULL, del);
}
arr[i] = NULL;
return (arr);
}
