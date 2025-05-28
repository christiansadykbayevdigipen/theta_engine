#include <cstring>
#include <iostream>
#include "application/application.h"
#include "core.h"
#include "theta.h"

theta_application g_app;
theta_application_descriptor g_descriptor;

void start(theta_application* app) {

}

void update(theta_application* app, f64 elapsed) {
    
}

void terminate(theta_application* app) {
    
}

int main() {
    strcat(g_descriptor.app_name, "Lambda, a Theta game engine editor.");
    g_descriptor.api = THETA_API_OPENGL;
    g_descriptor.cursor_lock = FALSE;
    g_descriptor.F11_does_fullscreen = FALSE;
    g_descriptor.starts_in_fullscreen = FALSE;
    g_descriptor.start = &start;
    g_descriptor.update = &update;
    g_descriptor.terminate = &terminate;

    theta_application_init(&g_app, g_descriptor);
    theta_application_run(&g_app);
    theta_application_destruct(&g_app);
}