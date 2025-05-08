#include "../../theta/src/theta.h"

#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

static theta_renderable g_renderable;

static theta_mat4x4f model;
static theta_mat4x4f view;
static theta_mat4x4f proj;

void sb_start() {

    theta_renderable_init_quad(&g_renderable);

    model = theta_mat4x4f_identity();
    view = theta_mat4x4f_identity();
    proj = theta_mat4x4f_orthographic();
}

void sb_update(f64 elapsed_time) {
    g_renderable.material.program.set_mvp(&g_renderable.material.program, model, view, proj);
    theta_renderer_submit(&g_renderable);
}

void sb_terminate() {
    
}

int main() {
    theta_application sandbox;
    theta_application_descriptor descriptor;
    strcpy_s(descriptor.app_name, MAX_STRING, "Sandbox");
    descriptor.start = sb_start;
    descriptor.update = sb_update;
    descriptor.terminate = sb_terminate;
    descriptor.api = THETA_API_OPENGL;
    theta_application_init(&sandbox, descriptor);
    theta_application_run(&sandbox);
    theta_application_destruct(&sandbox);
}