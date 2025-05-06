#pragma once

#include "core.h"

struct theta_rendering_context;

/*
@brief A window in Theta is where all the rendering goes to.
*/
typedef struct {
    void* uninterpreted_data;
    theta_api api;
    struct theta_rendering_context* context;
}theta_window;

/*
@brief This initializes the theta windowing system.
@param window An empty structure to be sent to theta for it to initialize.
@param width The width you would like the window to be (in pixels).
@param height The height you would like the window to be (in pixels).
@param title The title you wish to give the window.
@param api The api that you wish to initialize the window as
*/
THETA_API void theta_window_init(theta_window* window, u32 width, u32 height, const char* title, theta_api api);

/*
@brief This method checks to see if the theta window wishes to close. This can happen when the user presses the "X" button in the top right corner of the window (on windows). 
@param window An initialized theta_window structure.
*/
THETA_API BOOL theta_window_close_requested(theta_window* window);

/*
@brief This method updates the window. Allows the user to resize the window, poll events, and update systems in place for the renderer. This method should be called at the end of all rendering. This is because if the API is OpenGL, theta_window_update will also swap the buffers used for OpenGL.
@param window An initialized theta_window structure.
*/
THETA_API void theta_window_update(theta_window* window);

/*
@brief This method terminates the window.
@param window An initialized theta_window structure.
*/
THETA_API void theta_window_destroy(theta_window* window);