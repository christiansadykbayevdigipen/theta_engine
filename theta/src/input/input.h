#pragma once

#include "core.h"
#include "utils/list.h"

/*
@brief A structure denoting keyboard input. For example, if a game has a walk input binding, the input layout for the keyboard would set positive to be D, and negative to be A. Because D is walking toward the right, and A is walking toward the left.
@param positive The key on the keyboard that signifies a positive input choice.
@param negative The key on the keyboard that signifies a negative input choice. If this is NULL, then it is assumed that the input choice is binary instead of a range. For example, a reload button does not have a negative state, only a positive state or no state. So a reload button would have negative set to NULL.
*/
typedef struct {
    char positive;
    char negative;
}theta_input_layout_keyboard;

/*
@brief The input descriptor structure denoting a list of bindings in which they all fall under the same event for input. For example, walking has multiple bindings, for controller, for keyboard, etc. Keyboard would use the A and D keys for example, and joystick would use the left joystick. 
*/
typedef struct {
    char tag[MAX_STRING];
}theta_input_descriptor;

THETA_API void theta_input_bind_control(const char* tag);