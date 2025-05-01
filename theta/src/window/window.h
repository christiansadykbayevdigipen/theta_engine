#pragma once

#include "core.h"

/*
@brief A window in Theta is where all the rendering goes to.
*/
typedef struct {
    void* uninterpreted_data;
}theta_window;

/*
@brief This initializes the theta windowing system.
@param window An empty structure to be sent to theta for it to initialize.
@param width The width you would like the window to be (in pixels).
@param height The height you would like the window to be (in pixels).
@param The title you wish to give the window.
*/
THETA_API void theta_window_init(theta_window* window, u32 width, u32 height, const char* title);