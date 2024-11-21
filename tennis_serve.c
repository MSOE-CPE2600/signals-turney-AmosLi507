/**
 * Amos(Mohan) Li
 * CPE 2600-121
 * 11/20/2024
 * Lab 10-Signals
 * File: tennis_serve.c
 * Modified by: Amos(Mohan) Li
 * Compile Command: gcc -o tennis_serve tennis_serve.c
 * 
 * Brief summary of program: 
 */

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

int passing = 0;
pid_t receiver_pid;
// Signal handler for SIGUSR1
void handle_sigusr1(int signum, siginfo_t *info, void *context) {
    receiver_pid = info->si_pid;
    passing = info->si_value.sival_int;
    passing++;
    //receive the ball and hit it
    printf("Received the ball\n");
    printf("\007");

    //for 10 hits, the game ends
    if(passing == 10) {
        printf("game over\n");
        exit(0);
    }

    //wait for 1 or 2 seconds
    srand(time(NULL));
    int random_number = rand() % 2 + 1;
    sleep(random_number);

    union sigval value;
    value.sival_int = passing;

    // Print the random number being sent
    printf("Sending ball to server %d (#%d passing)\n", receiver_pid, passing);
    // Send the signal using sigqueue
    if (sigqueue(receiver_pid, SIGUSR1, value) == -1) {
        perror("Error sending signal");
        exit(1);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Wrong format");
        return 1;
    }
    // Get the target PID from the command line
    pid_t target_pid = atoi(argv[1]);

    // Serve the ball
    union sigval value;
    value.sival_int = passing;
    printf("Server %d is running.\n", getpid());
    printf("Serve the ball to %d.\n", target_pid);
    printf("\007");
    passing++;
    if (sigqueue(target_pid, SIGUSR1, value) == -1) {
        perror("Error serving");
        return 1;
    }

    //Set up the signal hadler to receive the ball
    struct sigaction sa;
    sa.sa_sigaction = handle_sigusr1;
    sa.sa_flags = SA_SIGINFO;
    sigemptyset(&sa.sa_mask);
    // Register the signal handler for SIGUSR1
    if (sigaction(SIGUSR1, &sa, NULL) == -1) {
        perror("Error registering signal handler");
        exit(1);
    }

    while (1) {
        pause();
    }

    return 0;
}
