#pragma once

#include "core.h"

/*
@brief This resets the theta timer to the current time.
*/
THETA_API void theta_timer_reset();

/*
@brief This checks the current time, and the last time that was saved into the theta timer (through theta_timer_reset), and calculates an elapsed time between the two time points. This returns the elapsed time in seconds.
*/
THETA_API f64 theta_timer_get_elapsed();
