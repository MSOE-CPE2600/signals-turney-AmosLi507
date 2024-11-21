/**
 * Amos(Mohan) Li
 * CPE 2600-121
 * 11/20/2024
 * Lab 10-Signals
 * File: signal_alarm.c
 * Modified by: Amos(Mohan) Li
 * Compile Command: gcc signal_alarm.c -o signal_alarm
 * Brief summary of program: This program schedules an alarm to be sent to after 5 seconds. 
 */

#include <stdio.h>
#include <unistd.h>
#include <signal.h>

//handle the signal SIGALRM and print the message
void handle_alarm(int sig) {
    if (sig == SIGALRM) {
        printf("Received SIGALRM: Timer expired!\n");
    }
}

int main() {
    //register for the signal
    signal(SIGALRM, handle_alarm);

    printf("Scheduling an alarm for 5 seconds...\n");
    alarm(5);

    printf("Waiting for the alarm...\n");
    pause();

    printf("Exiting program after handling SIGALRM.\n");
    return 0;
}