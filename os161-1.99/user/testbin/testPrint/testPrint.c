#include <unistd.h>
#include <stdio.h>


int exitcode = 42;

int
main()
{

  printf("Syscall for Integer Printing (if no. is divisible by 2)\n");
  int isDivisible;
    for (int i = 0; i < 5; i++) {
        isDivisible = printint(i); // Lab 2: Part C
        if (isDivisible == 0) {
          printf("Number is divisible by 2\n");
        } else {
          printf("Number is not divisible by 2\n");
        }
    }
  _exit(exitcode); // exit the thread - Part B

    printf("This should not be printed\n");
    return 0;
};




