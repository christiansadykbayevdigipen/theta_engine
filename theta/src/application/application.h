#pragma once

#include "core.h"

#include "window/window.h"

/*
@brief This is the data that theta needs to initialize the user defined application outlined in theta_application_init.
@param app_name This is the name you wish to give to the application
@param start This is the callback you wish to give to theta when you're application starts. 
@param update This is the callback you wish to give to theta that will be called each application update event. It also gives you an elapsed time for physics calculations.
@param api This is the api that you wish the application to be initialized for. This mainly applies to the renderer and windowing system.
*/
typedef struct {
    char app_name[MAX_STRING];
    void (*start)();
    void (*update)(f64 elapsed_time);
    theta_api api;
}theta_application_descriptor;

/*
@brief This is an application structure in which the user defines their version of the application.
*/
typedef struct {
    theta_application_descriptor descriptor;
    theta_window window;
}theta_application;

THETA_API void theta_application_init(theta_application* app, theta_application_descriptor descriptor);
THETA_API void theta_application_run(theta_application* app);