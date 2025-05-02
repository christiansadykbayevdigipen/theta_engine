#pragma once

#include "core.h"
#include "window/window.h"

#if defined(THETA_PLATFORM_SHARED)
#include <Windows.h>
#include <glfw/glfw3.h>

/*
@brief These are the specifics that will be filled out in theta_window's uninterpreted data. This is platform specific to the "shared platform," which includes windows, mac, and linux.
*/
typedef struct {
    GLFWwindow* window_handle;
    theta_api api;
}theta_shared_window_specifics;

/*
@brief This initializes theta's window as a shared window
*/
THETA_API void theta_window_init_shared_window(theta_window* window, u32 width, u32 height, const char* title, theta_api api);

/*
@brief This checks to see if theta's window should be closed as a shared window
*/
THETA_API BOOL theta_window_close_requested_shared_window(theta_window* window);

/*
@brief This updates the theta window as a shared window
*/
THETA_API void theta_window_update_shared_window(theta_window* window);

#else
#error You cannot include this header when you are not on the shared platform (windows, linux, mac).
#endif