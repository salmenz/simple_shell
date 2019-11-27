# simple_shell

## DESCRIPTION
A simple shell created for Holberton School project. Partner project with @rdsim8589 & @wintermanc3r

## QUICK START
To start up simple_shell, compile using `gcc -Wall -Werror -Wextra -pedantic *.c -o hsh`.

run
```
./hsh

```
## SYNOPSIS
simple_shell [command_string | file]

## DESCRIPTION
simple_shell is an sh-compatible command language interpreter that executes commands read from the standard input or from a file.

### Overview
The simple_shell is a command that reads lines from either a file or the terminal, interprets them, and generally executes other commands.  It is the program that is running when the user runs gcc -Wall -Werror -Wextra -pedantic *.c -o hsh and runs the executable file, ./hsh. The simple_shell implements a language that has flow control constructs, a macro facility that provides a variety of features in addition to data storage, along with built in history and line editing capabilities.  It incorporates many features to aid interactive use and has the advantage that the interpretative language is common to both interactive and non-interactive use (shell scripts).  That is, commands can be typed directly to the running shell or can be put into a file and the file can be executed directly by the shell.

### Simple Commands
 If a simple command has been recognized, the shell performs the following actions:

 1.   Leading words of the form “name=value” are stripped off and assigned to the environment of the simple command.  Redirection operators and their arguments (as described below) are stripped off and saved for processing.

 2.   The remaining words are expanded as described in the section called “Expansions”, and the first remaining word is considered the command name and the command is located.  The remaining words are considered the arguments of the command.  If no command name resulted, then the “name=value” variable assignments recognized in item 1 affect the current shell.


### Builtins
This section lists the builtin commands which are builtin because they need to perform some operation that can't be performed by a separate process. 

####alias [name[=string ...]]
If name=string is specified, the shell defines the alias name with value string.  If just name is specified, the value of the alias name is printed.  With no arguments, the alias builtin prints the names and values of all defined aliases (see unalias).

####cd [-LP] [directory]
Switch to the specified directory (default HOME).  If an entry for CDPATH appears in the environment of the cd command or the shell variable CDPATH is set and the directory name does not begin with a slash, then the directories listed in CDPATH will be searched for the specified directory.  The format of CDPATH is the same as that of PATH.  If a single dash is specified as the argument, it will be replaced by the value of OLDPWD.  The cd command will print out the name of the directory that it actually switched to if this is different from the name that the user gave.  These may be different either because the CDPATH mechanism was used or because the argument is a single dash.  The -P option causes the physical directory structure to be used, that is, all symbolic links are resolved to their respective values.  The -L option turns off the effect of any preceding -P options.


#### env  [-] [NAME=VALUE]... [COMMAND [ARG]...]
Prints out the current environment.

#### exit [exitstatus]
Terminate the shell process.  If exitstatus is given it is used as the exit status of the shell; otherwise the exit status of the preceding command is used.

#### help [PATTERN ...]
Display information about builtin commands.

#### history
Display the history list with line numbers.

#### setenv [VARIABLE] [VALUE]
The setenv() built-in adds the variable name to the environment with the value value, if name does not already exist. If name does exist in the environment, then its value is changed to value if overwrite is nonzero; if overwrite is zero, then the value of name is not changed. This function makes copies of the strings pointed to by name and value.

#### unsetenv [VARIABLE]
The unsetenv() built-in deletes the variable name from the environment. If name does not exist in the environment, then the functionsucceeds, and the environment is unchanged.


#### unalias [-a] [name]
If name is specified, the shell removes that alias.  If -a is specified, all aliases are removed.


### external functions
The simple shell will support all functions that can be found within a PATH

#### examples
ls, cat, and grep.p
