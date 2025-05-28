#pragma once

#include "core.h"

#include "window/window.h"
#include "input/input.h"

#define SEC_PER_UPDATE 0.016

struct theta_application;

/*
@brief This is the data that theta needs to initialize the user defined application outlined in theta_application_init.
@param app_name This is the name you wish to give to the application
@param start This is the callback you wish to give to theta when you're application starts.
@param update This is the callback you wish to give to theta that will be called each application update event. It also gives you an elapsed time for physics calculations.
@param terminate This is the callback you wish to give to theta that will be called when the application is terminated.
@param api This is the api that you wish the application to be initialized for. This mainly applies to the renderer and windowing system.
*/
typedef struct {
    char app_name[MAX_STRING];
    void (*start)(struct theta_application* app);
    void (*update)(struct theta_application* app, f64 elapsed_time);
    void (*terminate)(struct theta_application* app);
    theta_api api;
    BOOL starts_in_fullscreen;
    BOOL cursor_lock;
    BOOL F11_does_fullscreen;
    BOOL enable_imgui;
}theta_application_descriptor;

/*
@brief This is an application structure in which the user defines their version of the application.
*/
typedef struct theta_application{
    theta_application_descriptor descriptor;
    theta_window* window;
    theta_input_system* input;
}theta_application;

/*
@brief This initializes the theta application
@param descriptor A descriptor to the parameters of which this application should be initialized as.
@retuns The initialized application
*/
THETA_API void theta_application_init(theta_application* app, theta_application_descriptor descriptor);

/*
@brief This runs the application. This also starts the game loop. This will perform a while loop until the user requests the application to be closed. Hence, no function calls will be called after this in your main function, until the application has been requested to be terminated.
@param app A pointer to an initialized application structure.
*/
THETA_API void theta_application_run(theta_application* app);

/*
@brief This destructs the theta application. This should ideally be called after theta_application_run.
@param app This is a pointer to an initialized application structure.
*/
THETA_API void theta_application_destruct(theta_application* app);