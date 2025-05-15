#include "timer/timer.h"
#if defined THETA_PLATFORM_POSIX

#include <time.h>


static struct timespec g_start_time;

void theta_timer_reset() {
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &g_start_time);
}

f64 theta_timer_get_elapsed() {
	struct timespec end_time;
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end_time);
	long difference_in_nanoseconds = (end_time.tv_sec - g_start_time.tv_sec) * (long)1e9 + (end_time.tv_nsec - g_start_time.tv_nsec);
	f64 difference_converted = (f64)difference_in_nanoseconds;

	f64 difference_in_seconds = difference_converted / (1e+9);

	return difference_in_seconds;
}

#endif
