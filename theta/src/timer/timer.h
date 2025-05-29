#pragma once

#include "core.h"


typedef struct theta_timer{
    void* uninterpreted_data;
}theta_timer;

THETA_API void theta_timer_init(theta_timer* timer);

/*
@brief This resets the theta timer to the current time.
*/
THETA_API void theta_timer_reset(theta_timer* timer);

/*
@brief This checks the current time, and the last time that was saved into the theta timer (through theta_timer_reset), and calculates an elapsed time between the two time points. This returns the elapsed time in seconds.
*/
THETA_API f64 theta_timer_get_elapsed(theta_timer* timer);

THETA_API void theta_timer_destroy(theta_timer* timer);