// Lab 2: Q2: Implementing _exit()
#include <unistd.h>
#include <stdio.h>


int main(void){
    int exitCode = 42;

    printf("Exiting with code %d\n", exitCode);

    _exit(exitCode);

    printf("this should not be printed\n");

    return 0;
};


