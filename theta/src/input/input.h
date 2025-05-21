#pragma once

#include "core.h"
#include "utils/list.h"
#include "math/tmath.h"

#if defined(THETA_PLATFORM_SHARED)
#include "window/platform/shared/shared_window_keys.h"
#endif  

#define MAX_LAYOUTS 10

/*
@brief A structure denoting keyboard input. For example, if a game has a walk input binding, the input layout for the keyboard would set positive to be D, and negative to be A. Because D is walking toward the right, and A is walking toward the left.
@param positive The key on the keyboard that signifies a positive input choice.
@param negative The key on the keyboard that signifies a negative input choice. If this is NULL, then it is assumed that the input choice is binary instead of a range. For example, a reload button does not have a negative state, only a positive state or no state. So a reload button would have negative set to NULL.
*/
typedef struct {
    char positive;
    char negative;
}theta_input_layout_keyboard;

typedef enum {
    THETA_INPUT_LAYOUT_TYPE_KEYBOARD,
}theta_input_layout_type;

typedef struct {
    void* input_layout;
    theta_input_layout_type type;
}theta_input_layout;

/*
@brief The input descriptor structure denoting a list of bindings in which they all fall under the same event for input. For example, walking has multiple bindings, for controller, for keyboard, etc. Keyboard would use the A and D keys for example, and joystick would use the left joystick. 
*/
typedef struct {
    char tag[MAX_STRING];
    theta_input_layout layout[MAX_LAYOUTS];
    u32 layout_count;
    void (*input_callback)(theta_vector3f);
    s32 status; // Either -1, 0, or 1. Basically, the last direction it headed.
}theta_input_descriptor;

typedef struct theta_input_system{
    theta_input_descriptor* inputs;
}theta_input_system;

THETA_API theta_input_system* theta_input_system_init();

THETA_API void theta_input_system_bind_input(theta_input_system* system, const char* tag, theta_input_layout layout, void (*input_callback)(theta_vector3f));

THETA_API void theta_input_system_on_key_down(theta_input_system* system, char key);
THETA_API void theta_input_system_on_key_up(theta_input_system* system, char key);

THETA_API void theta_input_system_destroy(theta_input_system* system);