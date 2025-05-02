#include "application.h"

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

    while(!theta_window_close_requested(&app->window)) {
        // TODO: Fill in an actual value
        app->descriptor.update(0.0f);

        theta_window_update(&app->window);
    }
}