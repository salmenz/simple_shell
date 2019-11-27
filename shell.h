#ifndef _SHELL_H_
#define _SHELL_H_
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <limits.h>
#include <signal.h>
#define BUFSIZE 1024
#define TOK_BUFSIZE 64
#define LINE_DELIM " \t\r\n\a"
extern char  **environ;
/**
* struct builtin - builtin
* @str: string
* @builtin_func: funct
*/
typedef struct builtin
{
char *str;
int (*builtin_func)(char **);
} builtin_t;
char **splitline(char *line, char *del);
char *_strcat(char *s1, char *s2);
char *readline(void);
int _putchar(char c);
int _strcmp(char *s1, char *s2);
int builtin_cd(char **args);
int builtin_env(char **args);
int builtin_exit(char **args);
int builtin_help(char **args);
int builtin_setenv(char **args);
int builtin_unsetenv(char **args);
int exe_cmd(char **args);
int execute(char **args);
void _puts(char *str);
void sigintHandler(int sig_num);

#endif
