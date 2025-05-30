#include "timer/timer.h"
#if defined(THETA_PLATFORM_WIN32)

#include <Windows.h>
#include <malloc.h>

typedef struct {
    LARGE_INTEGER starting_time;
    LARGE_INTEGER frequency;
}theta_timer_windows_specifics;

void theta_timer_init(theta_timer* timer) {
    timer->uninterpreted_data = malloc(sizeof(theta_timer_windows_specifics));
    theta_timer_windows_specifics* self = DATA_CAST(theta_timer_windows_specifics, timer);
}

void theta_timer_reset(theta_timer* timer) {
    theta_timer_windows_specifics* self = DATA_CAST(theta_timer_windows_specifics, timer);
    
    QueryPerformanceFrequency(&self->frequency);
    QueryPerformanceCounter(&self->starting_time);
}

f64 theta_timer_get_elapsed(theta_timer* timer) {
    theta_timer_windows_specifics* self = DATA_CAST(theta_timer_windows_specifics, timer);
    
    LARGE_INTEGER ending_time;
    QueryPerformanceCounter(&ending_time);

    LARGE_INTEGER elapsed_microseconds;
    elapsed_microseconds.QuadPart = ending_time.QuadPart - self->starting_time.QuadPart;

    elapsed_microseconds.QuadPart *= 1000000;
    elapsed_microseconds.QuadPart /= self->frequency.QuadPart;

    f64 elapsed = (f64)elapsed_microseconds.QuadPart;

    elapsed /= (1e+6);

    return elapsed;
    return 0.1f;
}

void theta_timer_destroy(theta_timer* timer) {
    free(timer->uninterpreted_data);
}

#endif