#include "shell.h"
/**
 * exe_cmd - cmd function
 * @args: double pointer
 * Return: 1
 */
int exe_cmd(char **args)
{
pid_t pid;
int status;
pid = fork();
if (pid == 0)
{
if (execve(args[0], args, environ) == -1)
perror("ysh");
exit(EXIT_FAILURE);
}
else if (pid < 0)
perror("ysh");
else
{
do {
waitpid(pid, &status, WUNTRACED);
} while (!WIFEXITED(status) && !WIFSIGNALED(status));
}
return (1);
}
