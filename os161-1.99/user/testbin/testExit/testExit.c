#include <unistd.h>
#include <stdio.h>


int exitcode = 42;



int
main()
{
    printf("Killing the thread\n");
    printf("calling exit\n");
    _exit(exitcode); // Lab 2: Part B

    printf("This should not be printed since the thread is killed\n");
    return 0;
};




