## Simple Shell Program
This project is a simple shell program written in C that parses user input and translates it into executable commands. It includes support for several built-in commands and a few optional features. Below is a detailed description of the implemented commands and how to use them
 
## Features
The shell supports the following built-in commands:

# pwd: Print the current working directory.
Usage: pwd
Description: Displays the absolute path of the current working directory.

# echo: Print a user input string to stdout.
Usage: echo <string>
Example: echo Hello World
Description: Prints the provided string to the standard output.

# cp: Copy a file to another file.
Usage: cp <sourcePath> <targetPath>
Description: Copies the content of the source file to the target file.
If the target file not exists, an error message is printed.
If only a directory is provided as the target path, the source file name is used for the target file.
The -a option can be used to append the source content to the end of the target file.
Usage: cp -a <sourcePath> <targetPath>

# mv: Move a file to another location.
Usage: mv <sourcePath> <targetPath>
Description: Moves the source file to the target path.
If the target file exists, an error message is printed.
If only the source file path is provided, the target file will use the same name as the source file.
The -f option can be used to force overwrite the target file if it exists.
Usage: mv -f <sourcePath> <targetPath>

# exit: Terminate the shell.
Usage: exit
Description: Prints "good bye" and exits the shell.

# help: Display information about supported commands.
Usage: help
Description: Lists all the built-in commands with a brief description of each.
Building and Running

# To build and run the shell program, follow these steps:
1. gcc -static command.c Shell.c -o Shell
2. ./Shell
