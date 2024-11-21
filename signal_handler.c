/**
 * Amos(Mohan) Li
 * CPE 2600-121
 * 11/20/2024
 * Lab 10-Signals
 * Compile Command: gcc signal_handler.c -o signal_handler
 * @file signal_handler.c
 * @brief Sets a signal handler for SIGINT, the handler prints a message and then quits
 */

/**
 * Modified by: Amos Li
 * 
 * Brief summary of modifications: I deleted the line 27 exit(1),
 * so that the program won't exit after receiving the signal. to exit the program,
 * we need the command kill -SIGKILL <PID>
 */


#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * @brief Signal handler for SIGINT - prints a message and exits
 */
void handle_signal() {
    printf("Received a signal\n");
    //exit(1);//this line is deleted
}

int main() {

    // Register for the signal
    signal(SIGINT, handle_signal);

    // Wait until a signal is received
    while(1) {
        printf("Sleeping\n");
        sleep(1);
    }

    return 0;
}