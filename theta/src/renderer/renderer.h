#pragma once

#include "core.h"
#include "context/context.h"
#include "utils/list.h"

struct theta_mesh;
struct theta_shader_program;
struct theta_renderable;

/*
@brief The theta rendering structure. This is only used in renderer.c, and is used staticly. The renderer mainly just holds information about the renderer, rather than doing much of anything. 
*/
typedef struct {
    theta_window* window;
    theta_rendering_context* context;
    theta_dynamic_list rendering_list;
}theta_renderer;

/*
@brief This initializes the theta renderer.
@param window The window that the renderer should initialize with. Uses the API that the window is initialized with.
*/
THETA_API void theta_renderer_init(theta_window* window);

/*
@brief This method should be called BEFORE any rendering. Preps the frame for rendering.
*/
THETA_API void theta_renderer_begin_frame();

/*
@brief Submits a renderable to the rendering queue. Gets rendered at theta_renderer_end_frame.
*/
THETA_API void theta_renderer_submit(struct theta_renderable* renderable);

/*
@brief This method should be called AFTER all rendering. Finishes the frame and preps for the next frame.
*/
THETA_API void theta_renderer_end_frame();

/*
@returns The theta rendering context associated with the theta renderer
*/
THETA_API theta_rendering_context* theta_renderer_get_context();

/*
@returns The api that the renderer, context, and window is initialized under.
*/
THETA_API theta_api theta_renderer_get_api();

THETA_API void theta_renderer_destroy();