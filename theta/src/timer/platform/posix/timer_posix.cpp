#include "timer/timer.h"
#if defined THETA_PLATFORM_POSIX

#include <time.h>

// https://people.cs.rutgers.edu/~pxk/416/notes/c-tutorials/gettime.html

#define BILLION 1000000000L

static struct timespec g_start_time;

void theta_timer_reset() {
    clock_gettime(CLOCK_MONOTONIC, &g_start_time);
}

f64 theta_timer_get_elapsed() {
	struct timespec end_time;
	clock_gettime(CLOCK_MONOTONIC, &end_time);

	u64 diff = BILLION * (end_time.tv_sec - g_start_time.tv_sec) + end_time.tv_nsec - g_start_time.tv_nsec;
	f64 diff_converted = (f64)(diff);

	f64 difference_seconds = diff_converted / (1e+9);

	return difference_seconds;
}

#endif
