#include "timer.h"

#include <time.h>

clock_t g_system_time;

void theta_timer_reset() {
    g_system_time = clock();
}

f64 theta_timer_get_elapsed() {

    clock_t current_state = clock();

    clock_t new = current_state - g_system_time;

    f64 new_float = (f64)new;

    f64 divisor = (f64)CLOCKS_PER_SEC;

    f64 total_time = new_float / divisor;

    return total_time;
}