// Lab 2: Q2: Implementing _exit()

// #include <stdio.h>
#include <unistd.h>
// #include "include/unistd.h"
// #include "unistd.h"


// load header file for custom system call = printint

int main(void) {
    printint(10); // Lab 2: Q3 - Call the printint system call
    // printf("printint returned: %d\n", result);

    int exitCode = 42;
    // printf("Exiting with code %d\n", exitCode);

    // Call our custom system call - _exit with code
    _exit(exitCode);  // Use your custom system call here

    // printf("this should not be printed\n");

    return 0;
}

