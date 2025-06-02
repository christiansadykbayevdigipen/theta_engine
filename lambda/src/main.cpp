#include <cstring>
#include <iostream>
#include "application/application.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "cglm/cam.h"
#include "cglm/types.h"
#include "cglm/util.h"
#include "cglm/vec3.h"
#include "core.h"
#include "imgui_internal.h"
#include "object/camera.h"
#include "object/scene.h"
#include "object/scene_manager.h"
#include "renderer/mesh.h"
#include "renderer/shader.h"
#include "theta.h"

#include "imgui.h"
#include "timer/timer.h"

theta_application g_app;
theta_application_descriptor g_descriptor;

#define STRING_SIZE 512
#define CAMERA_MOVEMENT_SPEED 5.0f
#define CAMERA_ROTATION_SPEED 2.0f

void QueryInput(theta_application* app, f64 elapsed);

struct ObjectDetails 
{
    char ObjectName[STRING_SIZE];
    char WavefrontLocation[STRING_SIZE];
    float Position[3];
    float Rotation[3];
    float Scale[3];
    char AlbedoLocation[STRING_SIZE];
};

static theta_timer g_LeTimer;

void start(theta_application* app) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    ImGui::StyleColorsDark();

    void* handlea = (void*)app->window->get_window_handle(app->window);
    GLFWwindow* handle = static_cast<GLFWwindow*>(handlea);

    ImGui_ImplGlfw_InitForOpenGL(handle, TRUE);
    ImGui_ImplOpenGL3_Init();

    // Initialize scene stuff'
    theta_camera camera;
    mat4 projection;
    glm_perspective(glm_rad(90), 16.0f/9.0f, 0.001f, 1000.0f, projection);
    theta_camera_init(&camera, projection);
    theta_scene* scene = theta_scene_init(camera);
    theta_scene_manager_set_active_scene(scene);

    char texture_locations[6][MAX_STRING] = 
    {
        "res/right.jpg",
        "res/left.jpg",
        "res/top.jpg",
        "res/bottom.jpg",
        "res/front.jpg",
        "res/back.jpg",
    };
    //  char texture_locations[6][MAX_STRING] = 
    //  {
    //      "res/lightblue/right.png",
    //      "res/lightblue/left.png",
    //      "res/lightblue/top.png",
    //      "res/lightblue/bot.png",
    //      "res/lightblue/front.png",
    //      "res/lightblue/back.png",
    //  };

    theta_skybox skybox;

    theta_skybox_init(&skybox, texture_locations);

    theta_scene_give_skybox(scene, skybox);

    theta_timer_init(&g_LeTimer);
    theta_timer_reset(&g_LeTimer);
}

void update(theta_application* app, f64 elapsed) {
    QueryInput(app, elapsed);
}

void DrawViewport(theta_application* app) {
    bool is_open;
    ImGui::Begin("Viewport", &is_open, /*ImGuiWindowFlags_NoSavedSettings | */ImGuiWindowFlags_NoBackground);
    
    ImVec2 pos = ImGui::GetWindowPos();
    ImVec2 size = ImGui::GetContentRegionMax();
    
    f32 paddingX = ImGui::GetWindowSize().x - size.x;
    f32 paddingY = ImGui::GetWindowSize().y - size.y;

    pos.y = -pos.y;

    pos.y += theta_application_get_window_current_height(app) - size.y;

    pos.y -= paddingY * 2;

    theta_application_set_viewport(app, pos.x, pos.y, size.x, size.y);

    ImGui::End();
}

bool g_CreatingObject = false;

void DrawCreateObject(theta_application* app) {
    
    ImGui::Begin("aaa");

    if(ImGui::Button("Create Object.")) {
        g_CreatingObject = true;
    }

    ImGui::End();
}

void DrawObjectWizard(theta_application* app) {
    if(!g_CreatingObject) return;
    
    bool is_open;
    ImGui::Begin("Object Creation Wizard", &is_open/*, ImGuiWindowFlags_NoSavedSettings*/);

    static ObjectDetails details = {{0}, {0}, {0}, {0}, {0}};

    ImGui::InputText("Object name", details.ObjectName, STRING_SIZE);

    ImGui::Text("Transform Details");

    ImGui::InputFloat3("World Position", details.Position);

    ImGui::InputFloat3("World Rotation", details.Rotation);
    
    ImGui::InputFloat3("World Scale", details.Scale);

    ImGui::Text("Mesh Details");

    ImGui::InputText("Wavefront Object File location (.obj)", details.WavefrontLocation, STRING_SIZE);

    ImGui::Text("Material Details");

    ImGui::InputText("Albedo Texture Location", details.AlbedoLocation, STRING_SIZE);



    // This should be last.
    if(ImGui::Button("Finish Creation")) {
        theta_scene* scene = theta_scene_manager_get_active_scene();

        theta_mesh mesh;
        theta_material material;
        theta_shader_program shader;

        theta_mesh_init_from_file(&mesh, details.WavefrontLocation);
        material.albedo = theta_texture_init(details.AlbedoLocation);
        material.texture_tiling_x = 1;
        material.texture_tiling_y = 1;
        material.is_skybox = FALSE;
        material.uses_color = FALSE;
        
        material.ao = 1.0f;
        material.metallic = 0.5f;
        material.roughness = 0.5f;
        
        material.roughness_map = NULL;
        material.metallic_map = NULL;
        material.ao_map = NULL;
        material.normal_map = NULL;

        theta_shader_program_init_type(&shader, THETA_SHADER_TYPE_LIGHTING_SHADER_TEXTURED);

        theta_transform trsf;
        glm_vec3_copy(details.Position, trsf.position);
        glm_vec3_copy(details.Rotation, trsf.rotation);
        glm_vec3_copy(details.Scale, trsf.scale);

        theta_renderable* renderable = theta_renderable_init(mesh, material, shader);

        theta_game_object wip;
        theta_game_object_init(&wip, trsf, renderable, details.ObjectName);

        theta_scene_add_game_object(scene, wip);

        memset(&details, 0, sizeof(ObjectDetails));

        g_CreatingObject = false;
    }

    ImGui::End();
}

void QueryInput(theta_application* app, f64 elapsed) {
    // Camera movement
    if(ImGui::IsKeyDown(ImGuiKey_W)) {
        theta_camera* camera = &theta_scene_manager_get_active_scene()->bound_camera;

        vec3 forward;

        theta_camera_get_forward_vector(camera, forward);

        glm_vec3_scale(forward, elapsed*CAMERA_MOVEMENT_SPEED, forward);

        glm_vec3_add(camera->transform.position, forward, camera->transform.position);
    }
    if(ImGui::IsKeyDown(ImGuiKey_S)) {
        theta_camera* camera = &theta_scene_manager_get_active_scene()->bound_camera;

        vec3 forward;

        theta_camera_get_forward_vector(camera, forward);

        glm_vec3_scale(forward, elapsed*-CAMERA_MOVEMENT_SPEED, forward);

        glm_vec3_add(camera->transform.position, forward, camera->transform.position);
    }

    if(ImGui::IsKeyDown(ImGuiKey_D)) {
        theta_camera* camera = &theta_scene_manager_get_active_scene()->bound_camera;
        
        vec3 rot = {0.0f, 1.0f, 0.0f};

        glm_vec3_scale(rot, elapsed*CAMERA_MOVEMENT_SPEED, rot);
        
        glm_vec3_add(camera->transform.rotation, rot, camera->transform.rotation);
    }
    if(ImGui::IsKeyDown(ImGuiKey_A)) {
        theta_camera* camera = &theta_scene_manager_get_active_scene()->bound_camera;
        
        vec3 rot = {0.0f, 1.0f, 0.0f};

        glm_vec3_scale(rot, -elapsed*CAMERA_MOVEMENT_SPEED, rot);
        
        glm_vec3_add(camera->transform.rotation, rot, camera->transform.rotation);
    }
    if(ImGui::IsKeyDown(ImGuiKey_E)) {
        theta_camera* camera = &theta_scene_manager_get_active_scene()->bound_camera;
        
        vec3 poschange = {0.0f, 1.0f, 0.0f};

        glm_vec3_scale(poschange, -elapsed*CAMERA_MOVEMENT_SPEED, poschange);
        
        glm_vec3_add(camera->transform.position, poschange, camera->transform.position);
    }
    if(ImGui::IsKeyDown(ImGuiKey_Q)) {
        theta_camera* camera = &theta_scene_manager_get_active_scene()->bound_camera;
        
        vec3 poschange = {0.0f, -1.0f, 0.0f};

        glm_vec3_scale(poschange, -elapsed*CAMERA_MOVEMENT_SPEED, poschange);
        
        glm_vec3_add(camera->transform.position, poschange, camera->transform.position);
    }
}

static f64 frameTimeToDisplay = -5.0f;

void DrawProfiler(theta_application* app, f64 frame_time) {
    if(theta_timer_get_elapsed(&g_LeTimer) > 0.25f) {
        frameTimeToDisplay = frame_time;
        theta_timer_reset(&g_LeTimer);
    }

    ImGui::Begin("Lambda's Profiler");
    ImGui::Text("Frametime: %f", frameTimeToDisplay);
    ImGui::Text("Framerate: %f", 1.0f / frameTimeToDisplay);
    ImGui::End();
}

void DrawSceneHierarchy(theta_application* app) {
    theta_scene* scene = theta_scene_manager_get_active_scene();
    
    ImGui::Begin("Lambda Scene View");
    for(u32 i = 0; i < theta_scene_get_game_object_count(scene); i++) {
        theta_game_object* obj = theta_scene_get_game_objects(scene) + i;

        ImGui::Text("Object Name: %s", obj->identifier);
        ImGui::InputFloat3((std::string("Object Position") + std::string("##") + (char)i).c_str(), obj->transform.position);
        ImGui::InputFloat3((std::string("Object Rotation") + std::string("##") + (char)i).c_str(), obj->transform.rotation);
        ImGui::InputFloat3((std::string("Object Scale") + std::string("##") + (char)i).c_str(), obj->transform.scale);
        bool deleteResult = ImGui::Button((std::string("Delete Object") + std::string("##") + (char)i).c_str());

        if(deleteResult) {
            theta_scene_remove_game_object(scene, obj);
            continue;
        }
    }
    ImGui::End();
}

void render(theta_application* app, f64 frame_time) {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    ImGui::DockSpaceOverViewport();
    
    // Setup Viewport
    DrawViewport(app);


    DrawProfiler(app, frame_time);
    DrawCreateObject(app);
    DrawObjectWizard(app);
    DrawSceneHierarchy(app);
    
    
    
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void terminate(theta_application* app) {
    
}

int main() {
    std::strcat(g_descriptor.app_name, "Lambda, a Theta game engine editor.");
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