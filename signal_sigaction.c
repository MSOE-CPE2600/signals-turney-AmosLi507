/**
 * Amos(Mohan) Li
 * CPE 2600-121
 * 11/20/2024
 * Lab 10-Signals
 * File: signal_sigaction.c
 * Modified by: Amos(Mohan) Li
 * Compile Command: gcc -o signal_sigaction signal_sigaction.c
 * 
 * Brief summary of program: Send the SIGUSER1 in another signal: 
 * by command kill -SIGUSR1 <PID>, after receiving the signal, the pid
 * of the signal sending process is printed out
 */

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

// Signal handler function
void handle_sigusr1(int signum, siginfo_t *info, void *context) {
    printf("Received SIGUSR1 signal from process: %d\n", info->si_pid);
}

int main() {
    // Define the sigaction structure
    struct sigaction sa;
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = handle_sigusr1; 

    // Register the signal handler for SIGUSR1
    if (sigaction(SIGUSR1, &sa, NULL) == -1) {
        perror("Error registering SIGUSR1 handler");
        exit(EXIT_FAILURE);
    }

    printf("Waiting for SIGUSR1 signal. PID: %d\n", getpid());

    // Infinite loop to keep the program running
    while (1) {
        pause(); // Wait for signals
    }

    return 0;
}