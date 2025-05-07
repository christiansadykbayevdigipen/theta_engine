#include "shared_window.h"

#include "renderer/context/context.h"

#include <malloc.h>
#include <memory.h>
#include <stdio.h>

void theta_window_init_shared_window(theta_window* window, u32 width, u32 height, const char* title, theta_api api){
    THETA_PROFILE();
    switch(api) {
    case THETA_API_OPENGL:
        break;
    default:
        THETA_FATAL("theta_window_init_shared_window has failed. The reason being, the API you attempted to initialize the window with has not yet been implemented into theta, or the api value is invalid.\n");
        break;
    }
    
    window->uninterpreted_data = malloc(sizeof(theta_shared_window_specifics));

    if(GLFW_FALSE == glfwInit()) {
        THETA_FATAL("theta_window_init_shared_window has failed. The reason being, glfwInit (the window API used in this game engine) has failed.\n");
        return;
    }

    DATA_CAST(theta_shared_window_specifics, window)->window_handle = glfwCreateWindow(width, height, title, NULL, NULL);
    window->api = api;

    // If the API is OpenGL, make OpenGL Context current.
    if(window->api == THETA_API_OPENGL) {
        glfwMakeContextCurrent(DATA_CAST(theta_shared_window_specifics, window)->window_handle);
    }

    window->context = INIT_STRUCT(theta_rendering_context);
    theta_rendering_context_init(window->context, api, window);
}

BOOL theta_window_close_requested_shared_window(theta_window* window){
    return glfwWindowShouldClose(DATA_CAST(theta_shared_window_specifics, window)->window_handle);
}

void theta_window_update_shared_window(theta_window* window){
    glfwPollEvents();
}

void theta_window_destroy_shared_window(theta_window* window) {
    THETA_PROFILE();
    glfwTerminate();

    glfwDestroyWindow(DATA_CAST(theta_shared_window_specifics, window)->window_handle);
}

u32 theta_shared_window_get_proc_address(theta_window* window) {
    return glfwGetProcAddress;
}

void theta_shared_window_swap_buffers(theta_window *window) {
    THETA_ASSERT(window->api == THETA_API_OPENGL, "theta_shared_window_swap_buffers has failed. The reason being swap buffers can only be called if OpenGL is being used!");

    glfwSwapBuffers(DATA_CAST(theta_shared_window_specifics, window)->window_handle);
}