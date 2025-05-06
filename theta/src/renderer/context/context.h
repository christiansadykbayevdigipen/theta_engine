#pragma once

#include "core.h"

#include "window/window.h"

/*
@brief The rendering context is the low level access to things like vertex buffers, vertex arrays, (for OpenGL), swapchains (vulkan and direct x), etc.
It's the abstraction of these concepts so that the high level renderer can use these as another layer of abstraction
@param api The api the rendering context has been initialized under.
@param window The window the context should be displayed on
@param uninterpreted_data The data that each api has specific information under. 
*/
typedef struct theta_rendering_context{
    theta_api api;
    theta_window* window;
    void* uninterpreted_data;
}theta_rendering_context;

/*
@brief Initializes the theta rendering context
@param ctx A pointer to an uninitialized theta rendering contex structure
@param api The api to initialize the rendering context under. This must be the same context given to the window
@param window A pointer to a heap allocated theta window structure, that also must be initialized before given to this method
*/
THETA_API void theta_rendering_context_init(theta_rendering_context* ctx, theta_api api, theta_window* window);