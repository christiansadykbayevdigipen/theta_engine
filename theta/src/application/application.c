#include "application.h"

#include <stdio.h>

void theta_application_init(theta_application* app, theta_application_descriptor descriptor) {
    app->descriptor = descriptor;
}

void theta_application_run(theta_application* app) {
    app->descriptor.start();

    while(TRUE) {
        // TODO: Fill in an actual value
        app->descriptor.update(0.0f);
    }
}