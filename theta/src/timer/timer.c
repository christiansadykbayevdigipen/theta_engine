#include "timer.h"

#include <time.h>

clock_t g_system_time;

void theta_timer_reset() {
    g_system_time = clock();
}

f64 theta_timer_get_elapsed() {
    clock_t current_state = clock();

    f64 total_time = (f64)(current_state - g_system_time) / CLOCKS_PER_SEC;

    return total_time;
}