#include <types.h>
#include <lib.h>
#include <syscall.h>
#include <test.h>
#include <thread.h>
#include <kern/unistd.h>
#include <current.h>

// Lab 2: Part B
void sys___exit(int exitcode) {
    kprintf("exit: (%d)\n", exitcode);

    kprintf("Thread %s exited with code %d\n", curthread->t_name, exitcode);

    thread_exit();

    panic("sys__exit: Thread did not exit properly\n");
}

// Lab 2: Part C
int sys_printint(int c) { 
    kprintf("Given Number: %d\n", c);

    return (c % 2 == 0) ? 0 : 1;
}

// Implement a simplified system call named int reversestring(const char *str, int len) 

// This system call should accept a string and length of the string as input and print the reverse of the string 
// using the internal kprintf( ) function. The return value should be 1 if the length of the string is multiple of 
// 5 or 0 otherwise. 

// Lab 2: Part D
int sys_reversestring(const char *str, int len) { 
    kprintf("Given String: %s\n", str);

    for (int i = len - 1; i >= 0; i--) {
        kprintf("%c", str[i]);
    }

    kprintf("\n");

    return (len % 5 == 0) ? 1 : 0;
}

