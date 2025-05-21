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

namespace theta
{
    void SharedWindow::Init(u32 width, u32 height, const std::string& title, theta_api api)
    {
        THETA_PROFILE();

        switch (api)
        {
        case THETA_API_OPENGL:
            break;
        default:
            THETA_FATAL("theta_window_init_shared_window has failed. The reason being, the API you attempted to initialize the window with has not yet been implemented into theta, or the api value is invalid.\n");
            return;
            break;
        }

        m_Api = api;

        if (GLFW_FALSE == glfwInit())
        {
            THETA_FATAL("theta_window_init_shared_window has failed. The reason being, glfwInit (the window API used in this game engine) has failed.\n");
            return;
        }

        if (m_Api == THETA_API_OPENGL)
        {
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        }

        m_WindowHandle = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);

        // If the API is OpenGL, make OpenGL Context current.
        if (m_Api == THETA_API_OPENGL)
        {
            glfwMakeContextCurrent(m_WindowHandle);
        }
    }

    bool SharedWindow::CloseRequested()
    {
        return glfwWindowShouldClose(m_WindowHandle);
    }

    void SharedWindow::Update() 
    {
        glfwPollEvents();
    }

    void SharedWindow::CreateInputCallbacks(struct theta_input_system* inputSystem)
    {
        g_input_system = inputSystem;
    
        glfwSetKeyCallback(m_WindowHandle, _theta_window_shared_key_callback);
    }

    void SharedWindow::ChangeTitle(const std::string& newTitle)
    {
        glfwSetWindowTitle(m_WindowHandle, newTitle.c_str());
    }

    void SharedWindow::OpenGLSwapBuffers()
    {
        THETA_ASSERT(m_Api == THETA_API_OPENGL, "theta_shared_window_swap_buffers has failed. The reason being swap buffers can only be called if OpenGL is being used!");

        glfwSwapBuffers(m_WindowHandle);
    }
}