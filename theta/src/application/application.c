#include "application.h"
#include "timer/timer.h"

#include <string.h>
#include <stdio.h>

#include "renderer/renderer.h"

void theta_application_init(theta_application* app, theta_application_descriptor descriptor) {
    THETA_PROFILE();
    char full_window_name[MAX_STRING] = "[Powered by Theta] - ";

    strcat_s(full_window_name, MAX_STRING, descriptor.app_name);

    app->descriptor = descriptor;
    theta_window_init(&app->window, 1280, 720, full_window_name, descriptor.api);
    theta_renderer_init(&app->window);
}

void theta_application_run(theta_application* app) {
    THETA_PROFILE();
    if(app->descriptor.start != NULL) app->descriptor.start();

    theta_timer_reset();

    while(!theta_window_close_requested(&app->window)) {
        theta_renderer_begin_frame();
        


        f64 elapsed = theta_timer_get_elapsed();
        theta_timer_reset();

        if(app->descriptor.update != NULL) app->descriptor.update(elapsed);

        /*-----Rendering should go here-----*/
        
        /*-----!Rendering should go here-----*/

        
        theta_window_update(&app->window);
        theta_renderer_end_frame();
    }
}

void theta_application_destruct(theta_application* app) {
    if(app->descriptor.terminate != NULL) app->descriptor.terminate();
    
    theta_window_destroy(&app->window);
}