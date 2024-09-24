#include <types.h>
#include <kern/errno.h>
#include <kern/unistd.h>
#include <thread.h>
#include <lib.h>
#include <uio.h>
#include <syscall.h>
#include <vnode.h>
#include <vfs.h>
#include <current.h>
#include <proc.h>


int sys_printint(int c) { // Lab 2: Q3 - Add a prototype for printint
    // Print the integer
    kprintf("%d\n", c);

    // Return 0 if divisible by 2, otherwise return 1
    return (c % 2 == 0) ? 0 : 1;
};

/*
* System Call used to exit out of infinite loop
*/
void sys_exit(int exitCode){ // Lab 2: Q2: Implementing _exit()
	// handling the exit code
	kprintf("Exit code: %d\n", exitCode);

	//WE print the exit code here
	kprintf("Thread %s exited with code %d\n", curthread->t_name, exitCode);

	//clean up the thread - default/original thread exit code.
	thread_exit();

	//prevent returning after calling _exit
	panic("sys__exit: Thread did not exit properly\n");
};

