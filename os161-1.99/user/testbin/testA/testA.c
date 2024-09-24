#include <unistd.h>
#include <stdio.h>

int exitcode = 42;

// Lab 2: Part E. Create a test program, named testprint, to test the printint( ) system call developed in 
// Part C. Pass 5 integers (any) in a for loop and see if these are printed or not

int testprint()
{

    for (int i = 0; i < 5; i++) {
        printint(i); // Lab 2: Part C
    }
    _exit(exitcode); // Lab 2: Part B

    return 0;
};



// Lab 2: Part F. Create another test program, named testreverse to use the reversestring( ) system call 
// developed in Part D. Pass any string as argument.

int testreverse()
{
    reversestring("Hello", 5); // Lab 2: Part D
    _exit(exitcode); // Lab 2: Part B

    return 0;
};


int
main()
{

    printf("Syscall for Integer Printing (Even or Odd)\n");
    testprint(); // Lab 2: Part E

    printf("Syscall for String Reversal\n");
    testreverse(); // Lab 2: Part F

    _exit(exitcode); // Lab 2: Part B
    printf("This should not be printed\n");
    return 0;
};




