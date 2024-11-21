 /**
 * Amos(Mohan) Li
 * CPE 2600-121
 * 11/20/2024
 * Lab 10-Signals
 * @file signal_segfault.c
 * @brief Program that dereferences a null pointer causing a segmentation fault
 * Compile command line: gcc -o signal_segfault signal_segfault.c
 */

/**
 * Modified by: Amos(Mohan) Li
 * 
 * Brief summary of modifications: a signal handler for SIGSEGV
 * is added, and it print a message that a segmentation fault was received.
 * This program retry the null pointer dereference, and leads
 * to an infinite loop of signal handling.
 */


#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

//Handle the sigmentation fault signal
void handle_sigsegv(int signum) {
    printf("Segmentation fault (SIGSEGV) received.\n");
}

int main (int argc, char* argv[]) {
    signal(SIGSEGV, handle_sigsegv);
    // Declare a null pointer
    int* i = NULL;

    // Dereference the null pointer
    printf("The value of i is: %d\n", *i);

    // Return to exit the program
    return 0;
}