/**
 * Amos(Mohan) Li
 * CPE 2600-121
 * 11/20/2024
 * Lab 10-Signals
 * File: recv_signal.c
 * Modified by: Amos(Mohan) Li
 * Compile Command: gcc -o recv_signal recv_signal.c
 * 
 * Brief summary of program: uses sigaction to register a
 * handler for the SIGUSR1 signal, and it print out the random
 * number data along with the signal SIGUSER.
 */

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

// Signal handler for SIGUSR1
void handle_sigusr1(int signum, siginfo_t *info, void *context) {
    printf("Received SIGUSR1 with data: %d\n", info->si_value.sival_int);
}

int main() {
    // Define the sigaction structure
    struct sigaction sa;

    // Set the handler function and enable SA_SIGINFO
    sa.sa_sigaction = handle_sigusr1;
    sa.sa_flags = SA_SIGINFO;
    sigemptyset(&sa.sa_mask);

    // Register the signal handler for SIGUSR1
    if (sigaction(SIGUSR1, &sa, NULL) == -1) {
        perror("Error registering signal handler");
        exit(EXIT_FAILURE);
    }

    //prints out the pid, so that the signal will be send to this pid
    printf("Receiver running. PID: %d\n", getpid());
    printf("Waiting for SIGUSR1...\n");

    while (1) {
        pause();
    }

    return 0;
}
