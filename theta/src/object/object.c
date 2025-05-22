#include "object.h"

#include <malloc.h>
#include <memory.h>

#include "stb_ds.h"

void theta_game_object_init(theta_game_object* obj, theta_transform transform, theta_renderable* renderable, const char* identifier) {
    THETA_PROFILE();

    obj->components_length = 0;
    obj->transform = transform;
    strcpy(obj->identifier, identifier);

    theta_component c;
    c.data = renderable;
    c.type = THETA_COMPONENT_TYPE_RENDERABLE;

    theta_game_object_add_component(obj, c);
}

void theta_game_object_add_component(theta_game_object* obj, theta_component component) {
    THETA_PROFILE();
    if(obj->components_length + 1 > MAX_COMPONENTS) {
        THETA_ERROR("theta_game_object_add_component has failed. The reason being, the maximum number of components (%d) on a game object has been exceeded.\n", MAX_COMPONENTS);
        return;
    }

    if(theta_game_object_has_component(obj, component.type)) {
        THETA_ERROR("theta_game_object_add_component has failed. The reason being, there already is a component of the type supplied to this method.\n");
        return;
    }

    obj->components[obj->components_length] = component;

    obj->components_length++;
}

BOOL theta_game_object_has_component(theta_game_object* obj, theta_component_type type) {
    for(u32 i = 0; i < obj->components_length; i++) {
        if(obj->components[i].type == type) {
            return TRUE;
        }
    }

    return FALSE;
}

theta_component theta_game_object_get_component(theta_game_object *obj, theta_component_type type) {
    for (u32 i = 0; i < obj->components_length; i++) {
        if (obj->components[i].type == type) {
            return obj->components[i];
        }
    }

    THETA_ERROR("theta_game_object_get_component has failed. The reason being, there is no matches for the component type given to this theta game object.\n");
}

void theta_game_object_get_model(theta_game_object* obj, mat4 model) {
    mat4 model_matrix;
    glm_mat4_identity(model_matrix);

    glm_scale(model_matrix, obj->transform.scale);

    vec3 normalized;
    glm_vec3_copy(obj->transform.rotation, normalized);
    glm_normalize(normalized);
    f32 magnitude = glm_vec3_norm(obj->transform.rotation);
    
    glm_rotate(model_matrix, magnitude, normalized);

    glm_translate(model_matrix, obj->transform.position);

    glm_mat4_copy(model_matrix, model);
}

void theta_game_object_destroy(theta_game_object* obj) {
    THETA_PROFILE();
}