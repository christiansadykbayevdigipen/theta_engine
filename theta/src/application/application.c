#include "application.h"
#include "timer/timer.h"

#include <string.h>
#include <stdio.h>
#include <memory.h>
#include <malloc.h>

#include "renderer/renderer.h"
#include "object/scene_manager.h"

void theta_application_init(theta_application* app, theta_application_descriptor descriptor) {
    THETA_PROFILE();

    char full_window_name[MAX_STRING] = "[Powered by Theta] - ";

    strcat(full_window_name, descriptor.app_name);

    app->descriptor = descriptor;
    app->window = theta_window_init(1280, 720, full_window_name, descriptor.api);
    theta_renderer_init(app->window);

    app->input = theta_input_system_init();

    app->window->create_input_callbacks(app->window, app->input);

    app->window->set_fullscreen(app->window, app->descriptor.starts_in_fullscreen);
    app->window->set_cursor_lock(app->window, app->descriptor.cursor_lock);
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

    f64 t = 0.0;
    const f64 dt = 0.0166; // 60 Ticks per second

    theta_timer_reset();
    f64 accumulator = 0.0;
    while(!app->window->close_requested(app->window)) {
        f64 frame_time = theta_timer_get_elapsed();
        theta_timer_reset();

        accumulator += frame_time;

        theta_renderer_begin_frame();

        while(accumulator >= dt) {
            _theta_application_update(app, dt);
            accumulator -= dt;
            t += dt;
        }

        _theta_application_render(app);

        theta_renderer_end_frame();
    }
}

void theta_application_destruct(theta_application* app) {
    if(app->descriptor.terminate != NULL) app->descriptor.terminate();
    
    app->window->destroy(app->window);
    
    
}
