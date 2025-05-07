#include "renderer.h"

#include <memory.h>
#include <malloc.h>

#include "mesh.h"

static theta_renderer g_renderer;

void theta_renderer_init(theta_window* window) {
    THETA_PROFILE();
    g_renderer.window = window;
    g_renderer.context = INIT_STRUCT(theta_rendering_context);

    theta_rendering_context_init(g_renderer.context, window->api, window);
}

void theta_renderer_begin_frame() {
    g_renderer.context->clear(g_renderer.context);
}

void theta_renderer_submit(struct theta_mesh* mesh, struct theta_shader_program* program) {
    mesh->render(mesh, program);
}

void theta_renderer_end_frame() {
    g_renderer.context->swap(g_renderer.context);
}

theta_rendering_context* theta_renderer_get_context() {
    return g_renderer.context;
}

theta_api theta_renderer_get_api() {
    return g_renderer.context->api;
}