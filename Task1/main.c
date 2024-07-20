#include <stdio.h>

// Declare the external function and variable
extern void print_global();
extern int global_variable;

int main()
{
    printf("In main, global variable before calling function: %d\n", global_variable);
    print_global();
    return 0;
}
