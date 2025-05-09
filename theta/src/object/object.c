#include "object.h"

#include <malloc.h>
#include <memory.h>

void theta_game_object_init(theta_game_object* obj, theta_transform transform) {
    obj->components_length = 0;
    obj->transform = transform;
}

void theta_game_object_add_component(theta_game_object* obj, theta_component* component) {
    if(obj->components_length + 1 > MAX_COMPONENTS) {
        THETA_ERROR("theta_game_object_add_component has failed. The reason being, the maximum number of components (%d) on a game object has been exceeded.\n", MAX_COMPONENTS);
        return;
    }

    obj->components[obj->components_length] = component;

    obj->components_length++;
}

void theta_game_object_destroy(theta_game_object* obj) {
    for(u32 i = 0; i < obj->components_length; i++) {
        free(obj->components[i]);
    }
}