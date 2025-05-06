#pragma once

#include "core.h"
#include "window/window.h"

#if defined(THETA_PLATFORM_SHARED)
#include <glfw/glfw3.h>

/*
@brief These are the specifics that will be filled out in theta_window's uninterpreted data. This is platform specific to the "shared platform," which includes windows, mac, and linux.
*/
typedef struct {
    GLFWwindow* window_handle;
}theta_shared_window_specifics;

/*
@brief See theta_window_init
*/
THETA_API void theta_window_init_shared_window(theta_window* window, u32 width, u32 height, const char* title, theta_api api);

/*
@brief See theta_window_close_requested
*/
THETA_API BOOL theta_window_close_requested_shared_window(theta_window* window);

/*
@brief See theta_window_update
*/
THETA_API void theta_window_update_shared_window(theta_window* window);

/*
@brief See theta_window_destroy
*/
THETA_API void theta_window_destroy_shared_window(theta_window* window);

/*
@brief This is a method exclusive to shared window. Gets the proc address for opengl
@param window A pointer to an initialized theta_window structure. Must be initialized as a shared window.
@returns The proc address
*/
THETA_API u32 theta_shared_window_get_proc_address(theta_window* window);

#else
#error You cannot include this header when you are not on the shared platform (windows, linux, mac).
#endif