#include "../../theta/src/theta.h"

static void sb_start() {
    theta_camera temp_cam;
    theta_camera_init(&temp_cam, theta_mat4x4f_perspective_args(90, 1000.0f, 0.01f));
    theta_scene* scene = theta_scene_init(temp_cam);
}

static void sb_update(f64 elapsed) {

}

static void sb_terminate() {

}

theta_application_descriptor g_sandbox_descriptor = {
    "Sandbox",
    sb_start,
    sb_update,
    sb_terminate,
    THETA_API_OPENGL
};

int main() {
    theta_application app;
    theta_application_init(&app, g_sandbox_descriptor);
    theta_application_run(&app);
    theta_application_destruct(&app);
}