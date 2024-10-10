#include <unistd.h>
#include <stdio.h>


int exitcode = 42;


/* Lab 2: Part F. Create another test program, named testreverse to
 use the reversestring( ) system call developed in Part D. 
 Pass any string as argument. */

int
main()
{

  // Lab 2: Part D
    reversestring("Hello", 5); // returning whether the length of the string is multiple of 5 or not in kernel function.
    _exit(exitcode); // Lab 2: Part B

    printf("This should not be printed\n");
    return 0;
};




