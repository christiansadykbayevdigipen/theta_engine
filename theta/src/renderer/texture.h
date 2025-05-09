#pragma once 

#include "core.h"

typedef struct theta_texture {
    void* uninterpreted_data;
}theta_texture;

THETA_API void theta_texture_init(theta_texture* texture, const char* filepath);