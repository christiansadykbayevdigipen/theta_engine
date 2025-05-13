#include "shared_window.h"

#include "renderer/context/context.h"
#include "input/input.h"

#include <malloc.h>
#include <memory.h>
#include <stdio.h>

static theta_input_system* g_input_system;

static void _theta_window_shared_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if(action == GLFW_RELEASE)
        theta_input_system_on_key_up(g_input_system, key);
    if(action == GLFW_PRESS)
        theta_input_system_on_key_down(g_input_system, key);
}

theta_window* theta_window_init_shared_window(u32 width, u32 height, const char* title, theta_api api) {
    THETA_PROFILE();
    
    theta_window* window = INIT_STRUCT(theta_window);
    
    switch(api) {
    case THETA_API_OPENGL:
        break;
    default:
        THETA_FATAL("theta_window_init_shared_window has failed. The reason being, the API you attempted to initialize the window with has not yet been implemented into theta, or the api value is invalid.\n");
        return NULL;
        break;
    }
    
    window->uninterpreted_data = malloc(sizeof(theta_shared_window_specifics));

    if(GLFW_FALSE == glfwInit()) {
        THETA_FATAL("theta_window_init_shared_window has failed. The reason being, glfwInit (the window API used in this game engine) has failed.\n");
        return NULL;
    }

    DATA_CAST(theta_shared_window_specifics, window)->window_handle = glfwCreateWindow(width, height, title, NULL, NULL);
    window->api = api;

    // If the API is OpenGL, make OpenGL Context current.
    if(window->api == THETA_API_OPENGL) {
        glfwMakeContextCurrent(DATA_CAST(theta_shared_window_specifics, window)->window_handle);
    }

    window->context = theta_rendering_context_init(api, window);

    /*Initialize Function Pointers*/
    window->update = &theta_window_update_shared_window;
    window->close_requested = &theta_window_close_requested_shared_window;
    window->destroy = &theta_window_destroy_shared_window;
    window->create_input_callbacks = &theta_window_create_input_callbacks_shared_window;
    window->change_title = &theta_window_change_title_shared_window;

    return window;
}

BOOL theta_window_close_requested_shared_window(theta_window* window){
    return glfwWindowShouldClose(DATA_CAST(theta_shared_window_specifics, window)->window_handle);
}

void theta_window_update_shared_window(theta_window* window){
    glfwPollEvents();
}

void theta_window_destroy_shared_window(theta_window* window) {
    THETA_PROFILE();
    //glfwDestroyWindow(DATA_CAST(theta_shared_window_specifics, window)->window_handle);
    //glfwTerminate();


    
    window->context->destroy(window->context);
    free(window->uninterpreted_data);
}

u32 theta_shared_window_get_proc_address(theta_window* window) {
    return (u32)glfwGetProcAddress;
}

void theta_shared_window_swap_buffers(theta_window *window) {
    THETA_ASSERT(window->api == THETA_API_OPENGL, "theta_shared_window_swap_buffers has failed. The reason being swap buffers can only be called if OpenGL is being used!");

    glfwSwapBuffers(DATA_CAST(theta_shared_window_specifics, window)->window_handle);
}

void theta_window_create_input_callbacks_shared_window(theta_window* window, struct theta_input_system* input_system) {
    g_input_system = input_system;
    
    glfwSetKeyCallback(DATA_CAST(theta_shared_window_specifics, window)->window_handle, _theta_window_shared_key_callback);
}

void theta_window_change_title_shared_window(theta_window* window, const char* new_title) {
    glfwSetWindowTitle(DATA_CAST(theta_shared_window_specifics, window)->window_handle, new_title);
}