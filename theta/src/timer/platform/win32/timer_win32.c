#include "timer/timer.h"
#if defined(THETA_PLATFORM_WIN32)

#include <Windows.h>

LARGE_INTEGER g_starting_time;
LARGE_INTEGER g_frequency;

void theta_timer_init(theta_timer* timer) {
    
}

void theta_timer_reset(theta_timer* timer) {
    QueryPerformanceFrequency(&g_frequency);
    QueryPerformanceCounter(&g_starting_time);
}

f64 theta_timer_get_elapsed(theta_timer* timer) {
    LARGE_INTEGER ending_time;
    QueryPerformanceCounter(&ending_time);

    LARGE_INTEGER elapsed_microseconds;
    elapsed_microseconds.QuadPart = ending_time.QuadPart - g_starting_time.QuadPart;

    elapsed_microseconds.QuadPart *= 1000000;
    elapsed_microseconds.QuadPart /= g_frequency.QuadPart;

    f64 elapsed = (f64)elapsed_microseconds.QuadPart;

    elapsed /= (1e+6);

    return elapsed;
}

#endif