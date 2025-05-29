#include "shared_window.h"

#include "renderer/context/context.h"
#include "input/input.h"

#include <malloc.h>
#include <memory.h>
#include <stdio.h>

static void _theta_window_shared_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    theta_input_system* input_system = ((theta_window*)glfwGetWindowUserPointer(window))->input_system;
    
    if(action == GLFW_RELEASE)
        theta_input_system_on_key_up(input_system, key);
    if(action == GLFW_PRESS)
        theta_input_system_on_key_down(input_system, key);
}

static void _theta_window_shared_cursor_callback(GLFWwindow* window, double xPos, double yPos) {
    theta_input_system* input_system = ((theta_window*)glfwGetWindowUserPointer(window))->input_system;

    theta_input_system_on_cursor(input_system, xPos, yPos);
}

static void _theta_window_shared_resize_callback(GLFWwindow* window, int width, int height) {
    theta_rendering_context* rendering_context = ((theta_window*)glfwGetWindowUserPointer(window))->context;
    
    rendering_context->resize(rendering_context, width, height);
}

int test();

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
    window->api = api;

    if(GLFW_FALSE == glfwInit()) {
        THETA_FATAL("theta_window_init_shared_window has failed. The reason being, glfwInit (the window API used in this game engine) has failed.\n");
        return NULL;
    }

    if(window->api == THETA_API_OPENGL) {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    }

    DATA_CAST(theta_shared_window_specifics, window)->window_handle = glfwCreateWindow(width, height, title, NULL, NULL);
    DATA_CAST(theta_shared_window_specifics, window)->called_cursor_last_frame = FALSE;

    // If the API is OpenGL, make OpenGL Context current.
    if(window->api == THETA_API_OPENGL) {
        glfwMakeContextCurrent(DATA_CAST(theta_shared_window_specifics, window)->window_handle);
    }

    window->context = theta_rendering_context_init(api, window);

    glfwSetFramebufferSizeCallback(DATA_CAST(theta_shared_window_specifics, window)->window_handle, _theta_window_shared_resize_callback);

    glfwSetWindowUserPointer(DATA_CAST(theta_shared_window_specifics, window)->window_handle, window);

    /*Initialize Function Pointers*/
    window->update = &theta_window_update_shared_window;
    window->close_requested = &theta_window_close_requested_shared_window;
    window->destroy = &theta_window_destroy_shared_window;
    window->create_input_callbacks = &theta_window_create_input_callbacks_shared_window;
    window->change_title = &theta_window_change_title_shared_window;
    window->set_fullscreen = &theta_window_set_fullscreen_shared_window;
    window->set_cursor_lock = &theta_window_set_cursor_lock_shared_window;
    window->get_window_handle = &theta_window_get_window_handle_shared_window;

    window->width = width;
    window->height = height;


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
    
    // Must be a bug with GLFW. But calling glfwTerminate causes segmentation fault.
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
    window->input_system = input_system;
    glfwSetKeyCallback(DATA_CAST(theta_shared_window_specifics, window)->window_handle, _theta_window_shared_key_callback);
    glfwSetCursorPosCallback(DATA_CAST(theta_shared_window_specifics, window)->window_handle, _theta_window_shared_cursor_callback);
}

void theta_window_change_title_shared_window(theta_window* window, const char* new_title) {
    glfwSetWindowTitle(DATA_CAST(theta_shared_window_specifics, window)->window_handle, new_title);
}

void theta_window_set_fullscreen_shared_window(theta_window* window, BOOL fullscreen) {
    if(!fullscreen) {
        glfwSetWindowMonitor(DATA_CAST(theta_shared_window_specifics, window)->window_handle, NULL, 0, 0, window->width, window->height, GLFW_DONT_CARE);
        return;
    }

    u32 count = 0;
    GLFWmonitor** mons = glfwGetMonitors(&count);

    if(count == 0) return;

    s32 highest_hz = 0;
    u32 best_monitor = 0;
    const GLFWvidmode* best_monitor_vidmode = NULL;
    
    // Get the best monitor based on the highest refresh rate.
    for(u32 i = 0; i < count; i++) {
        const GLFWvidmode* mode = glfwGetVideoMode(mons[i]);
        if(mode->refreshRate > highest_hz) {
            highest_hz = mode->refreshRate;
            best_monitor = i;
            best_monitor_vidmode = mode;
        }
    }

    glfwSetWindowMonitor(DATA_CAST(theta_shared_window_specifics, window)->window_handle, mons[best_monitor], 0, 0, best_monitor_vidmode->width, best_monitor_vidmode->height, GLFW_DONT_CARE);
}

void theta_window_set_cursor_lock_shared_window(theta_window* window, BOOL cursor_lock) {
    if(cursor_lock)
        glfwSetInputMode(DATA_CAST(theta_shared_window_specifics, window)->window_handle, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    else
        glfwSetInputMode(DATA_CAST(theta_shared_window_specifics, window)->window_handle, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void* theta_window_get_window_handle_shared_window(theta_window* window) {
    return (void*)DATA_CAST(theta_shared_window_specifics, window)->window_handle;
}