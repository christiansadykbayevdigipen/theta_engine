#include "application.h"
#include "timer/timer.h"

#include <string.h>
#include <stdio.h>
#include <memory.h>
#include <malloc.h>

#include "renderer/renderer.h"
#include "object/scene_manager.h"

namespace theta
{
    Application::Application(const ApplicationDescriptor &descriptor):
        m_Descriptor(descriptor)
    {
        THETA_PROFILE();

        std::string concattedString = "[Powered by Theta] - " + m_Descriptor.ApplicationName;

        m_Window = IWindow::CreateWindow(m_Descriptor.Width, m_Descriptor.Height, concattedString, m_Descriptor.Api);
        theta_renderer_init(m_Window);
        m_Input = theta_input_system_init();

        //m_Window->create_input_callbacks(m_Window, m_Input);
        m_Window->CreateInputCallbacks(m_Input);
    }

    Application::~Application()
    {
        THETA_PROFILE();
        Terminate();

        theta_input_system_destroy(m_Input);
        theta_renderer_destroy();
    }

    void Application::Run()
    {
        THETA_PROFILE();
        Start();

        theta_timer_reset();

        f64 t = 0.0;
        const f64 dt = 0.0166; // 60 Ticks per second

        theta_timer_reset();
        f64 accumulator = 0.0;
        while (!m_Window->CloseRequested())
        {
            f64 frame_time = theta_timer_get_elapsed();
            theta_timer_reset();

            accumulator += frame_time;

            theta_renderer_begin_frame();

            while (accumulator >= dt)
            {
                _Update(dt);
                accumulator -= dt;
                t += dt;
            }

            _Render();

            theta_renderer_end_frame();
        }
    }

    void Application::_Render()
    {
        theta_scene *scene = theta_scene_manager_get_active_scene();
        if (scene != NULL)
        {
            theta_scene_render(scene);
        }
    }

    void Application::_Update(f64 elapsedTime)
    {
        Update(elapsedTime);
        theta_scene *scene = theta_scene_manager_get_active_scene();
        if (scene != NULL)
        {
            theta_scene_update(scene);
        }

        m_Window->Update();
    }
}