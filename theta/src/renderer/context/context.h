#pragma once

#include "core.h"

#include "window/window.h"

/*
@brief The rendering context is the low level access to things like vertex buffers, vertex arrays, (for OpenGL), swapchains (vulkan and direct x), etc.
It's the abstraction of these concepts so that the high level renderer can use these as another layer of abstraction
@param api The api the context is initialized under
@param window The window the context is initialize for
@param uninterpreted_data The API specific data that is used in the APIcontext implementations
@param clear Clears the screen. Wipes it clean
@param swap Initiates the swapchain or swaps buffers, depending on what API you use.
*/
typedef struct theta_rendering_context{
    theta_api api;
    theta_window* window;
    void* uninterpreted_data;

    void (*clear)(struct theta_rendering_context*);
    void (*swap)(struct theta_rendering_context*);
    void (*destroy)(struct theta_rendering_context*);
}theta_rendering_context;

/*
@brief Initializes the theta rendering context
@param ctx A pointer to an uninitialized theta rendering contex structure
@param api The api to initialize the rendering context under. This must be the same context given to the window
@param window A pointer to a heap allocated theta window structure, that also must be initialized before given to this method
*/
THETA_API theta_rendering_context* theta_rendering_context_init(theta_api api, theta_window* window);