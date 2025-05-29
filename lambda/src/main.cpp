#include <cstring>
#include <iostream>
#include "application/application.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "core.h"
#include "theta.h"

#include "imgui.h"

theta_application g_app;
theta_application_descriptor g_descriptor;

void start(theta_application* app) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

    ImGui::StyleColorsDark();

    void* handlea = (void*)app->window->get_window_handle(app->window);
    GLFWwindow* handle = static_cast<GLFWwindow*>(handlea);

    ImGui_ImplGlfw_InitForOpenGL(handle, TRUE);
    ImGui_ImplOpenGL3_Init();
}

void update(theta_application* app, f64 elapsed) {

}

void render(theta_application* app) {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    
    ImGui::Begin("Hello, world!");
    
    ImGui::End();
    
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void terminate(theta_application* app) {
    
}

int main() {
    strcat(g_descriptor.app_name, "Lambda, a Theta game engine editor.");
    g_descriptor.api = THETA_API_OPENGL;
    g_descriptor.cursor_lock = FALSE;
    g_descriptor.F11_does_fullscreen = FALSE;
    g_descriptor.starts_in_fullscreen = FALSE;
    g_descriptor.start = &start;
    g_descriptor.update = &update;
    g_descriptor.render = &render;
    g_descriptor.terminate = &terminate;

    theta_application_init(&g_app, g_descriptor);
    theta_application_run(&g_app);
    theta_application_destruct(&g_app);
}