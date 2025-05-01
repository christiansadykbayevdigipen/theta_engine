#include "shared_window.h"

#include <malloc.h>
#include <memory.h>

void theta_window_init_shared_window(theta_window* window, u32 width, u32 height, const char* title){
    window->uninterpreted_data = malloc(sizeof(theta_shared_window_specifics));

    if(GLFW_FALSE == glfwInit()) {
        THETA_FATAL("theta_window_init_shared_window has failed. The reason being, glfwInit (the window API used in this game engine) has failed.\n");
        return;
    }

    DATA_CAST(theta_shared_window_specifics, window)->window_handle = glfwCreateWindow(width, height, title, NULL, NULL);
}