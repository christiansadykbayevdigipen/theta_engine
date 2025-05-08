#include "renderer.h"

#include <memory.h>
#include <malloc.h>

#include "mesh.h"
#include "renderable.h"

static theta_renderer g_renderer;

void theta_renderer_init(theta_window* window) {
    THETA_PROFILE();
    g_renderer.window = window;
    g_renderer.context = INIT_STRUCT(theta_rendering_context);

    theta_rendering_context_init(g_renderer.context, window->api, window);

    theta_dynamic_list_init(&g_renderer.rendering_list, sizeof(theta_renderable*));
}

void theta_renderer_begin_frame() {
    g_renderer.context->clear(g_renderer.context);
}

void theta_renderer_submit(struct theta_renderable* renderable) {
    //renderable->mesh.render(&renderable->mesh, &renderable->material.program);
    theta_dynamic_list_push_back(&g_renderer.rendering_list, &renderable);
}

void theta_renderer_end_frame() {
    // Render everything in the stack
    for(s32 i = g_renderer.rendering_list.length-1; i >= 0; i--) {
        theta_renderable* r = ((theta_renderable*)theta_dynamic_list_get(&g_renderer.rendering_list, i));
        r->mesh.render(&r->mesh, &r->material);
        theta_dynamic_list_pop_back(&g_renderer.rendering_list);
    }

    g_renderer.context->swap(g_renderer.context);
}

theta_rendering_context* theta_renderer_get_context() {
    return g_renderer.context;
}

theta_api theta_renderer_get_api() {
    return g_renderer.context->api;
}

void theta_renderer_destroy() {
    g_renderer.context->destroy(g_renderer.context);
    free(g_renderer.context);
}