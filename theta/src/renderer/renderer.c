#include "renderer.h"

#include <memory.h>
#include <malloc.h>

#include "mesh.h"
#include "renderable.h"

#include "stb_ds.h"

static theta_renderer g_renderer;

void theta_renderer_init(theta_window* window) {
    THETA_PROFILE();
    g_renderer.window = window;
    g_renderer.context = window->context;
    g_renderer.is_skybox_bound = FALSE;
    g_renderer.submitted_renderables = NULL;
}

void theta_renderer_begin_frame() {
    g_renderer.context->clear(g_renderer.context);
}

void theta_renderer_submit(struct theta_renderable* renderable) {
    arrins(g_renderer.submitted_renderables, 0, renderable);
}

void theta_renderer_bind_skybox(theta_skybox skybox) {
    g_renderer.is_skybox_bound = TRUE;
    g_renderer.skybox = skybox;
}

BOOL theta_renderer_get_skybox(theta_skybox** skybox) {
    if(g_renderer.is_skybox_bound) {
        (*skybox) = &g_renderer.skybox;
        return TRUE;
    }
    else {
        (*skybox) = NULL;
        return FALSE;
    }
}

void theta_renderer_end_frame() {
    if(g_renderer.is_skybox_bound) {
        g_renderer.skybox.render(&g_renderer.skybox);
    }

    // Render everything in the queue
    u32 length = arrlen(g_renderer.submitted_renderables);
    for(u32 i = 0; i < length; i++) {
        theta_renderable* renderable = g_renderer.submitted_renderables[0];

        renderable->mesh.render(&renderable->mesh, &renderable->program);
        
        arrdel(g_renderer.submitted_renderables, 0);
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
    THETA_PROFILE();

    arrfree(g_renderer.submitted_renderables);
}