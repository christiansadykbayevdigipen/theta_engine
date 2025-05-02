#include "application.h"
#include "timer/timer.h"

#include <string.h>
#include <stdio.h>

void theta_application_init(theta_application* app, theta_application_descriptor descriptor) {
    char full_window_name[MAX_STRING] = "[Powered by Theta] - ";

    strcat_s(full_window_name, MAX_STRING, descriptor.app_name);

    app->descriptor = descriptor;
    theta_window_init(&app->window, 1280, 720, full_window_name, descriptor.api);
}

void theta_application_run(theta_application* app) {
    app->descriptor.start();

    theta_timer_reset();

    while(!theta_window_close_requested(&app->window)) {
        
        f64 elapsed = theta_timer_get_elapsed();
        theta_timer_reset();

        app->descriptor.update(elapsed);
        theta_window_update(&app->window);
    }
}