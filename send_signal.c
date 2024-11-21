/**
 * Amos(Mohan) Li
 * CPE 2600-121
 * 11/20/2024
 * Lab 10-Signals
 * File: send_signal.c
 * Modified by: Amos(Mohan) Li
 * Compile Command: gcc -o send_signal send_signal.c
 * 
 * Brief summary of program: This program sends the signal SIGUSER1 to the
 * assigned PID. I random generated number is stored in the signal
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Wrong format");
        return 1;
    }

    // Get the target PID from the command line
    pid_t target_pid = atoi(argv[1]);

    //Get a random number
    srand(time(NULL));
    int random_number = rand() % 100;

    // Set up the signal value to send
    union sigval value;
    value.sival_int = random_number;

    // Print the random number being sent
    printf("Sending SIGUSR1 to process %d with data: %d\n", target_pid, random_number);

    // Send the signal using sigqueue
    if (sigqueue(target_pid, SIGUSR1, value) == -1) {
        perror("Error sending signal");
        return 1;
    }

    return 0;
}
