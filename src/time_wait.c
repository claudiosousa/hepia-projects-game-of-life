/**
 * Some helper functions for managing execution time.
 * @author David Gonzalez, Claudio Sousa
 */

#include <stdio.h>
#include <unistd.h>
#include "time_wait.h"

static const double MICROSECONDS_IN_SECOND = 1000000;

/**
 * Starts a time wait
 * @param tm Structure to hold the starting time
 */
void time_wait_start(struct timespec *tm) {
    if (clock_gettime(CLOCK_MONOTONIC, tm) != 0)
        perror("Time start failed");
}

/**
 * Make the calling thread wait the time remaining
 * @param start_time Starting time
 * @param frequency Expected execution freqeuncy in Hz
 */
void time_wait_freq(struct timespec *start_time, int frequency) {
    int wait_time = MICROSECONDS_IN_SECOND / frequency;
    struct timespec end_time;

    if (clock_gettime(CLOCK_MONOTONIC, &end_time) == 0) {
        wait_time -= (end_time.tv_sec - start_time->tv_sec) * MICROSECONDS_IN_SECOND;
        wait_time -= (end_time.tv_nsec - start_time->tv_nsec) / 1000;
        if (wait_time > 0) {
            usleep(wait_time);
        }
    } else {
        perror("Time stop failed");
    }

    time_wait_start(start_time);
}
