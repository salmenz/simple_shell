#include "shell.h"
static builtin_t builtins[] = {
{"cd", builtin_cd},
{"help", builtin_help},
{"exit", builtin_exit},
{"env", builtin_env},
{"setenv", builtin_setenv},
{"unsetenv", builtin_unsetenv}};
/**
 * builtin_cd - cd function
 * @args: double pointer
 * Return: 1
 */
int builtin_cd(char **args __attribute__((unused)))
{
char *nom = getenv("_");
if (args[1] == NULL)
perror(nom);
else
{
if (chdir(args[1]) != 0)
perror(nom);
}
return (1);
}
/**
 * builtin_env - env function
 * @args: double pointer
 * Return: 1
 */
int builtin_env(char **args __attribute__((unused)))
{
int i;
for (i = 0; environ[i]; i++)
{
_puts(environ[i]);
_putchar('\n');
}
return (1);
}
/**
 * builtin_exit - exit function
 * @args: double pointer
 * Return: 1
 */
int builtin_exit(char **args __attribute__((unused)))
{
if (args[1])
exit(atoi(args[1]));
return (0);
}
/**
 * builtin_help - help function
 * @args: double pointer
 * Return: 1
 */
int builtin_help(char **args __attribute__((unused)))
{
int i;
for (i = 0; i < 5; i++)
{
_puts(builtins[i].str);
_putchar('\n');
}
return (1);
}
/**
 * builtin_setenv - setenv function
 * @args: double pointer
 * Return: 1
 */
int builtin_setenv(char **args __attribute__((unused)))
{
int i = 0, j;
char *variale;
if (!args[1] && !args[2])
{
_puts("USAGE: setenv NAME VALUE\n");
return (1);
}
else
{
variale = _strcat(args[1], "=");
variale = _strcat(variale, args[2]);
}
while (environ[i])
{
j = 0;
while (args[1][j] == environ[i][j])
j++;
if (environ[i][j] == '=')
{
environ[i] = variale;
return (1);
}
i++;
}
environ[i] = variale;
environ[i + 1] = NULL;
return (1);
}
/**
 * builtin_unsetenv - unsetenv function
 * @args: double pointer
 * Return: 1
 */
int builtin_unsetenv(char **args __attribute__((unused)))
{
int i = 0, j;
if (args[1] == NULL)
{
_puts("USAGE: unsetenv NAME VALUE\n");
return (1);
}
while (environ[i])
{
j = 0;
while (args[1][j] == environ[i][j])
j++;
if (environ[i][j] == '=')
{
while (environ[i] != NULL)
{
environ[i] = environ[i + 1];
i++;
}
environ[i - 1] = NULL;
break;
}
i++;
}
return (1);
}
#include "shell.h"
/**
 * execute - execute function
 * @args: double pointer
 * Return: args
 */
int execute(char **args __attribute__((unused)))
{
int i;
char **arr;
struct stat st;
char *path_var;
char *tmp;
char *cmd;
path_var = getenv("PATH");
if (args[0] == NULL)
return (1);
for (i = 0; builtins[i].str; i++)
{
if (strcmp(args[0], builtins[i].str) == 0)
return ((*builtins[i].builtin_func)(args));
}
arr = splitline(strdup(path_var), ":");
for (i = 0; arr[i]; i++)
{
tmp = _strcat(arr[i], "/");
cmd = _strcat(tmp, args[0]);
if (stat(cmd, &st) == 0)
{
args[0] = cmd;
break;
}
else if (stat(args[0], &st) == 0)
{
break;
}
}
return (exe_cmd(args));
}
