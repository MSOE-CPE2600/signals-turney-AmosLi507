/**
 * Amos(Mohan) Li
 * CPE 2600-121
 * 11/20/2024
 * Lab 10-Signals
 * File: tennis_receive.c
 * Modified by: Amos(Mohan) Li
 * Compile Command: gcc -o tennis_receive tennis_receive.c
 * 
 * Brief summary of program: 
 */

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

int passing = 0;
pid_t sender_pid;
// Signal handler for SIGUSR1
void handle_sigusr1(int signum, siginfo_t *info, void *context) {
    sender_pid = info->si_pid;
    passing = info->si_value.sival_int;
    passing++;
    //receive the ball and hit it
    printf("Received the ball \n");
    printf("\007");

    //for 10 hits, the game ends
    if(passing == 10) {
        printf("game over");
        exit(0);
    }

    //wait for 1 or 2 seconds
    srand(time(NULL));
    int random_number = rand() % 2 + 1;
    sleep(random_number);

    union sigval value;
    value.sival_int = passing;

    // Print the random number being sent
    printf("Sending ball to server %d, (#%d passing)\n", sender_pid, passing);

    // Send the signal using sigqueue
    if (sigqueue(sender_pid, SIGUSR1, value) == -1) {
        perror("Error sending signal");
        exit(1);
    }
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
    printf("Receiver waiting for the ball...\n");

    while (1) {
        pause();
    }

    return 0;
}
