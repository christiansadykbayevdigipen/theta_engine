#include "../../theta/src/theta.h"

#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

f32 vertices[] = {
    -0.5f, -0.5f,
    0.5f, -0.5f,
    0.0f, 0.5f
};

static theta_mesh g_test_mesh;
static theta_shader_program g_test_shader;

static theta_mat4x4f model;
static theta_mat4x4f view;
static theta_mat4x4f proj;

void sb_start() {
    theta_mesh_init(&g_test_mesh, vertices, sizeof(vertices) / sizeof(vertices[0]), 2);
    theta_shader_program_init(&g_test_shader, "res/basic_shader.shader");

    model = theta_mat4x4f_identity();
    view = theta_mat4x4f_identity();
    proj = theta_mat4x4f_orthographic();
}

void sb_update(f64 elapsed_time) {
    g_test_shader.set_mvp(&g_test_shader, model, view, proj);
    theta_renderer_submit(&g_test_mesh, &g_test_shader);
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