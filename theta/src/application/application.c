#include "application.h"
#include "timer/timer.h"

#include <string.h>
#include <stdio.h>
#include <memory.h>
#include <malloc.h>

#include "renderer/renderer.h"
#include "object/scene_manager.h"

theta_application* theta_application_init(theta_application_descriptor descriptor) {
    theta_application* app = INIT_STRUCT(theta_application);

    THETA_PROFILE();
    char full_window_name[MAX_STRING] = "[Powered by Theta] - ";

    strcat(full_window_name, descriptor.app_name);

    app->descriptor = descriptor;
    app->window = theta_window_init(1280, 720, full_window_name, descriptor.api);
    theta_renderer_init(app->window);

    app->input = theta_input_system_init();

    app->window->create_input_callbacks(app->window, app->input);

    return app;
}

static void _theta_application_update(theta_application* app, f64 elapsed) {
    if(app->descriptor.update != NULL) app->descriptor.update(elapsed);
    theta_scene* scene = theta_scene_manager_get_active_scene();
    if(scene != NULL) {
        theta_scene_update(scene);
    }
    
    app->window->update(app->window);
}

static void _theta_application_render(theta_application* app) {
    theta_scene* scene = theta_scene_manager_get_active_scene();
    if(scene != NULL) {
        theta_scene_render(scene);
    }
}

void theta_application_run(theta_application* app) {
    THETA_PROFILE();
    if(app->descriptor.start != NULL) app->descriptor.start();

    theta_timer_reset();

    /*Old deprecated broken stupid game loop*/
    while(!app->window->close_requested(app->window)) {
        theta_renderer_begin_frame();

        f64 elapsed = theta_timer_get_elapsed();
        theta_timer_reset();

        if(app->descriptor.update != NULL) app->descriptor.update(elapsed);

        theta_scene* scene = theta_scene_manager_get_active_scene();

        if(scene != NULL) {
            theta_scene_render(scene);
            theta_scene_update(scene);
        }
        
        app->window->update(app->window);
        theta_renderer_end_frame();
    }
}

void theta_application_destruct(theta_application* app) {
    if(app->descriptor.terminate != NULL) app->descriptor.terminate();
    
    app->window->destroy(app->window);

    theta_input_system_destroy(app->input);

    free(app);
}
