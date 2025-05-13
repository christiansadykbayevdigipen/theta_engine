#pragma once

#include "core.h"

// TODO: Migrate window system to use function pointer type system.

struct theta_rendering_context;
struct theta_input_system;

/*
@brief A window in Theta is where all the rendering goes to.
*/
typedef struct theta_window{
    void* uninterpreted_data;
    theta_api api;
    struct theta_rendering_context* context;

    BOOL (*close_requested)(struct theta_window*);
    void (*update)(struct theta_window*);
    void (*destroy)(struct theta_window*);
    void (*create_input_callbacks)(struct theta_window*, struct theta_input_system* input_system);
    void (*change_title)(struct theta_window*, const char* new_title);
}theta_window;

/*
@brief This initializes the theta windowing system.
@param width The width you would like the window to be (in pixels).
@param height The height you would like the window to be (in pixels).
@param title The title you wish to give the window.
@param api The api that you wish to initialize the window as
*/
THETA_API theta_window* theta_window_init(u32 width, u32 height, const char* title, theta_api api);