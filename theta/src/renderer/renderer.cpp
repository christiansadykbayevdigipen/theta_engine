#include "renderer.h"

#include <memory.h>
#include <malloc.h>

#include "mesh.h"
#include "renderable.h"

static theta_renderer g_renderer;

void theta_renderer_init(theta_window* window) {
    THETA_PROFILE();
    g_renderer.window = window;
    g_renderer.context = window->context;

    g_renderer.rendering_list = NULL;
}

void theta_renderer_begin_frame() {
    g_renderer.context->clear(g_renderer.context);
}

void theta_renderer_submit(struct theta_renderable* renderable) {
    //renderable->mesh.render(&renderable->mesh, &renderable->material.program);
    if(g_renderer.rendering_list == NULL) {
        g_renderer.rendering_list = theta_node_init(renderable, sizeof(theta_renderable));
        return;
    }

    g_renderer.rendering_list = theta_node_push_back(g_renderer.rendering_list, renderable, sizeof(theta_renderable));
}

void theta_renderer_end_frame() {
    // for(s32 i = g_renderer.rendering_list.length-1; i >= 0; i--) {
    //     theta_renderable* r = ((theta_renderable*)theta_dynamic_list_get(&g_renderer.rendering_list, i));
    //     r->mesh.render(&r->mesh, &r->program);
    //     theta_dynamic_list_pop_back(&g_renderer.rendering_list);
    // }


    // Render everything in the queue
    theta_node* temp_node = g_renderer.rendering_list;
    while(temp_node != NULL) {
        theta_renderable* renderable = (theta_renderable*)temp_node->data;
        renderable->mesh.render(&renderable->mesh, &renderable->program);
        
        temp_node = temp_node->next; // Set the node to the next node in the list

        // Remove the node at the beginning
        g_renderer.rendering_list = theta_node_delete_at_head(g_renderer.rendering_list);
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
}