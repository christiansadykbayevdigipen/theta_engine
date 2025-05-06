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

void sb_start() {
    theta_vector3f a = theta_vector3f_create_args(1.0f, 33.0f, 7.0f);
    
    a = theta_vector3f_muls(a, 2.0f);

    THETA_DEBUG("Vector %f,%f,%f\n", a.x, a.y, a.z);

    theta_mesh_init(&g_test_mesh, vertices, sizeof(vertices) / sizeof(vertices[0]), 2);
}

void sb_update(f64 elapsed_time) {
    theta_renderer_submit(&g_test_mesh);
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