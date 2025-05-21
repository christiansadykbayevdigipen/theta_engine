#pragma once

#include "core.h"

#include "window/window.h"
#include "input/input.h"

#include <string>

#define SEC_PER_UPDATE 0.016

// /*
// @brief This is the data that theta needs to initialize the user defined application outlined in theta_application_init.
// @param app_name This is the name you wish to give to the application
// @param start This is the callback you wish to give to theta when you're application starts.
// @param update This is the callback you wish to give to theta that will be called each application update event. It also gives you an elapsed time for physics calculations.
// @param terminate This is the callback you wish to give to theta that will be called when the application is terminated.
// @param api This is the api that you wish the application to be initialized for. This mainly applies to the renderer and windowing system.
// */
// typedef struct {
//     char app_name[MAX_STRING];
//     void (*start)();
//     void (*update)(f64 elapsed_time);
//     void (*terminate)();
//     theta_api api;
// }theta_application_descriptor;

// /*
// @brief This is an application structure in which the user defines their version of the application.
// */
// typedef struct {
//     theta_application_descriptor descriptor;
//     theta_window* window;
//     theta_input_system* input;
// }theta_application;

// /*
// @brief This initializes the theta application
// @param descriptor A descriptor to the parameters of which this application should be initialized as.
// @retuns The initialized application
// */
// THETA_API theta_application* theta_application_init(theta_application_descriptor descriptor);

// /*
// @brief This runs the application. This also starts the game loop. This will perform a while loop until the user requests the application to be closed. Hence, no function calls will be called after this in your main function, until the application has been requested to be terminated.
// @param app A pointer to an initialized application structure.
// */
// THETA_API void theta_application_run(theta_application* app);

// /*
// @brief This destructs the theta application. This should ideally be called after theta_application_run.
// @param app This is a pointer to an initialized application structure.
// */
// THETA_API void theta_application_destruct(theta_application* app);

namespace theta
{
    struct ApplicationDescriptor
    {
        s32 Width, Height;
        std::string ApplicationName;
        theta_api Api;
    };

    // A basic application class. Override this with your Game class.
    class Application
    {
    public:
        Application(const ApplicationDescriptor &descriptor);
        ~Application();

        void Run();

        // Override these functions if you wish.
        virtual void Start() {}
        virtual void Update(f64 elapsedTime) {}
        virtual void Terminate() {}

        theta_input_system* GetInput() {return m_Input;}
    private:
        void _Update(f64 elapsedTime);
        void _Render();
    private:
        theta_window* m_Window;
        theta_input_system* m_Input;
        ApplicationDescriptor m_Descriptor;
    };
}