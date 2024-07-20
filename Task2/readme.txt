# ELF Parser Application

This application parses an ELF file and prints its header content, similar to the `readelf -h` command. Additionally, it can list the names, sizes, and types of all ELF sections if they exist.

## Files

- `readelf.c`&'task2.c': Contains the source code for the ELF parser .
- 'task2'&'readelf' : contains the executalbe file.
- 'result.txt: contains the results from readelf and task2   

## Compilation

To compile the ELF parser application, follow these steps:

1. **Ensure you have a C compiler** (e.g., GCC) installed on your system.

2. **Compile the source code** using the following command:
    gcc -static readelf.c -o readelf

## Running the Program

To run the program, use the following command:
./readelf <option>
note: options are -h or -s but -s has not been finalized yet

