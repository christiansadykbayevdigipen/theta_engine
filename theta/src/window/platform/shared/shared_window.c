#include "shared_window.h"

#include <malloc.h>
#include <memory.h>
#include <stdio.h>

void theta_window_init_shared_window(theta_window* window, u32 width, u32 height, const char* title, theta_api api){
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
    DATA_CAST(theta_shared_window_specifics, window)->api = api;
}

BOOL theta_window_close_requested_shared_window(theta_window* window){
    return glfwWindowShouldClose(DATA_CAST(theta_shared_window_specifics, window)->window_handle);
}

void theta_window_update_shared_window(theta_window* window){
    glfwPollEvents();
    
    if(DATA_CAST(theta_shared_window_specifics, window)->api == THETA_API_OPENGL) {
        glfwSwapBuffers(DATA_CAST(theta_shared_window_specifics, window)->window_handle);
    }
}

void theta_window_destroy_shared_window(theta_window* window) {
    glfwTerminate();

    glfwDestroyWindow(DATA_CAST(theta_shared_window_specifics, window)->window_handle);
}