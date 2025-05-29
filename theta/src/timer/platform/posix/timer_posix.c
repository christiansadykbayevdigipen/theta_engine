#include "timer/timer.h"
#if defined THETA_PLATFORM_POSIX

#include <malloc.h>

#include <time.h>

// https://people.cs.rutgers.edu/~pxk/416/notes/c-tutorials/gettime.html

#define BILLION 1000000000L

typedef struct {
	struct timespec start_time;
}theta_timer_posix_specifics;

void theta_timer_init(theta_timer* timer) {
	theta_timer_posix_specifics* self = (theta_timer_posix_specifics*)timer->uninterpreted_data;
	
	timer->uninterpreted_data = malloc(sizeof(theta_timer_posix_specifics));
}

void theta_timer_reset(theta_timer* timer) {
	theta_timer_posix_specifics* self = (theta_timer_posix_specifics*)timer->uninterpreted_data;
    
	clock_gettime(CLOCK_MONOTONIC, &self->start_time);
}

f64 theta_timer_get_elapsed(theta_timer* timer) {
	theta_timer_posix_specifics* self = (theta_timer_posix_specifics*)timer->uninterpreted_data;
	
	struct timespec end_time;
	clock_gettime(CLOCK_MONOTONIC, &end_time);

	u64 diff = BILLION * (end_time.tv_sec - self->start_time.tv_sec) + end_time.tv_nsec - self->start_time.tv_nsec;
	f64 diff_converted = (f64)(diff);

	f64 difference_seconds = diff_converted / (1e+9);

	return difference_seconds;
}

void theta_timer_destroy(theta_timer* timer) {
	free(timer->uninterpreted_data);
}

#endif
