# C Program with Multiple Files
This project consists of two C files: one defining a function and global variables, and another containing the `main` function.

## Files

- `functions.c`: Contains a global variable and a function to print its value.
- 'function.i'&'main.i': contains a preprocessed C source file.
- `main.c`: Contains the `main` function that uses the function defined in `functions.c`.
- 'main.o'&'function.o': are an object file, which is an intermediate file generated during the compilation process of a C program. 
- 'main' : is an executable file.
- 'main.txt'&'function.txt' : contains the symbol table of the object files.
- 'program.txt' : contains the symbol table of the executable file.
- 'size_output.txt': contains the size .text and .data sections for the object files and executable file.
 

## Compilation

To compile the program, follow these steps:

1. Compile `functions.c` into an object file:
    gcc -c functions.c -o functions.o

2. Compile `main.c` into an object file:
    gcc -c main.c -o main.o

3. Link the object files to create the executable:
    gcc functions.o main.o -o program

## Running the Program

To run the program, use the following command:
./program

## Inspecting the Symbol Table and save its content in text file
   for object files :
    readelf -s function.o > function.txt
    readelf -s main.o > main.txt
   for executable file :
    readelf -s main > program.txt 

## Get the size of .data and .text for each section and save the content in text file
command : size function.o main.o main > size_output.txt 

## Example of the output 
     sybmol table of the function object file 

Symbol table '.symtab' contains 7 entries:
   Num:    Value          Size Type    Bind   Vis      Ndx Name
     0: 0000000000000000     0 NOTYPE  LOCAL  DEFAULT  UND
     1: 0000000000000000     0 FILE    LOCAL  DEFAULT  ABS function.c
     2: 0000000000000000     0 SECTION LOCAL  DEFAULT    1 .text
     3: 0000000000000000     0 SECTION LOCAL  DEFAULT    5 .rodata
     4: 0000000000000000     4 OBJECT  GLOBAL DEFAULT    3 global_variable
     5: 0000000000000000    39 FUNC    GLOBAL DEFAULT    1 print_global
     6: 0000000000000000     0 NOTYPE  GLOBAL DEFAULT  UND printf


      symbol table of the main object file 
Symbol table '.symtab' contains 8 entries:
   Num:    Value          Size Type    Bind   Vis      Ndx Name
     0: 0000000000000000     0 NOTYPE  LOCAL  DEFAULT  UND
     1: 0000000000000000     0 FILE    LOCAL  DEFAULT  ABS main.c
     2: 0000000000000000     0 SECTION LOCAL  DEFAULT    1 .text
     3: 0000000000000000     0 SECTION LOCAL  DEFAULT    5 .rodata
     4: 0000000000000000    53 FUNC    GLOBAL DEFAULT    1 main
     5: 0000000000000000     0 NOTYPE  GLOBAL DEFAULT  UND global_variable
     6: 0000000000000000     0 NOTYPE  GLOBAL DEFAULT  UND printf
     7: 0000000000000000     0 NOTYPE  GLOBAL DEFAULT  UND print_global


