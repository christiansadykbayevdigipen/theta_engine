#pragma once

#include "core.h"
#include "window/window.h"

#if defined(THETA_PLATFORM_SHARED)
#include <GLFW/glfw3.h>

struct theta_rendering_context;

/*
@brief These are the specifics that will be filled out in theta_window's uninterpreted data. This is platform specific to the "shared platform," which includes windows, mac, and linux.
*/
typedef struct {
    GLFWwindow* window_handle;
}theta_shared_window_specifics;

/*
@brief See theta_window_init
*/
//THETA_API theta_window* theta_window_init_shared_window(u32 width, u32 height, const char* title, theta_api api);

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

/*
@brief This swaps the buffers with GLFW. Can only be called if using OpenGL.
@param window A pointer to an initialized theta_window structure. Must be initialized as a shared window.
*/
THETA_API void theta_shared_window_swap_buffers(theta_window* window);

THETA_API void theta_window_create_input_callbacks_shared_window(theta_window* window, struct theta_input_system* input_system);

THETA_API void theta_window_change_title_shared_window(theta_window* window, const char* new_title);


namespace theta
{
    class SharedWindow : public IWindow
    {
    public:
        virtual void Init(u32 width, u32 height, const std::string& title, theta_api api) override;
        virtual bool CloseRequested() override;
        virtual void Update() override;
        virtual void CreateInputCallbacks(struct theta_input_system* inputSystem) override;
        virtual void ChangeTitle(const std::string& newTitle) override;
        virtual theta_api GetApi() override {return m_Api;}

        void OpenGLSwapBuffers();
    private:
        GLFWwindow* m_WindowHandle;
        theta_api m_Api;
    };
}


#else
#error You cannot include this header when you are not on the shared platform (windows, linux, mac).
#endif