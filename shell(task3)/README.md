# Shell Program
## Introduction
Welcome to the Extended Shell! This shell extends basic functionality by including a set of built-in commands with a few enhancements and new features. It also supports executing external commands 
found in the system's PATH. The shell ensures efficient resource management and avoids memory leaks.

## Features
### Built-in Commands

The following built-in commands are supported, with renamed duplicates to avoid conflicts with external commands:

    ### mycp: Copy files (equivalent to cp).
    Usage: cp <sourcePath> <targetPath>
    Description: Copies the content of the source file to the target file.
    If the target file not exists, an error message is printed.
    If only a directory is provided as the target path, the source file name is used for the target file.
    The -a option can be used to append the source content to the end of the target file.
    Usage: cp -a <sourcePath> <targetPath>
    
    ### mymv: Move/rename files (equivalent to mv).
    Usage: mv <sourcePath> <targetPath>
    Description: Moves the source file to the target path.
    If the target file exists, an error message is printed.
    If only the source file path is provided, the target file will use the same name as the source file.
    The -f option can be used to force overwrite the target file if it exists.
    Usage: mv -f <sourcePath> <targetPath>
    #### pwd: Print the current working directory .
    Usage: pwd
    Description: Displays the absolute path of the current working directory.
    #### echo: Display a line of text.
    Usage: echo <string>
    Description: Prints the provided string to the standard output.
    #### cd: change directory
    Description: command is used to change the current working directory to a specified path. If the path is valid and accessible, the shell will change the directory to the specified path.
    #### type:
    Description: command is used to identify the type of a command. It checks whether the command is an internal command (built-in), an external command (found in the system's PATH), 
    or an unsupported command.
    #### myenv: print all the environment variable (equivalent to env).
    #### help: 
    Description: Display help information about the shell .
    #### exit: Exit the shell .
### External Commands

    Supports executing any external program found in the system's PATH environment variable.
    Enables direct execution of programs without needing to specify the full path.

## To build and run the shell program, follow these steps:
1. gcc -static command.c Shell.c -o Shell
2. ./Shell
