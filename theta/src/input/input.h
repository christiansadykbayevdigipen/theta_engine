#pragma once

#include "core.h"
#include "utils/list.h"
#include <cglm/ivec3.h>

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
    theta_key_code positive;
    theta_key_code negative;
}theta_input_layout_keyboard;

typedef enum {
    THETA_INPUT_LAYOUT_TYPE_KEYBOARD,
    THETA_INPUT_LAYOUT_TYPE_CURSOR,
}theta_input_layout_type;


// Note if the input type is CURSOR, you can effectively make input_layout = NULL.
typedef struct {
    void* input_layout;
    theta_input_layout_type type;
}theta_input_layout;


// The input descriptor structure denoting a list of bindings in which they all fall under the same event for input. For example, walking has multiple bindings, for controller, for keyboard, etc. Keyboard would use the A and D keys for example, and joystick would use the left joystick. 
typedef struct {
    char tag[MAX_STRING];
    theta_input_layout layout[MAX_LAYOUTS];
    u32 layout_count;
    void (*input_callback)(vec3);
    s32 status; // Either -1, 0, or 1. Basically, the last direction it headed.
}theta_input_descriptor;

typedef struct theta_input_system{
    theta_input_descriptor* inputs;
    vec2 previous_cursor_position;
}theta_input_system;

// Initializes the theta input system
THETA_API theta_input_system* theta_input_system_init();

// Binds an input for a particular action.
// If that action does not exist yet, it creates it
// If an action already exists, it binds a new input type for that action
THETA_API void theta_input_system_bind_input(theta_input_system* system, const char* tag, theta_input_layout layout, void (*input_callback)(vec3));

// More or less reserved for the window backend
THETA_API void theta_input_system_on_key_down(theta_input_system* system, theta_key_code key);
// More or less reserved for the window backend
THETA_API void theta_input_system_on_key_up(theta_input_system* system, theta_key_code key);

// More or less reserved for the window backend
THETA_API void theta_input_system_on_cursor(theta_input_system* system, f64 x_position, f64 y_position);

// This should be called after all user defined updates have been called and all rendering.
THETA_API void theta_input_system_after_update(theta_input_system* system);

// Destroys the input system.
THETA_API void theta_input_system_destroy(theta_input_system* system);