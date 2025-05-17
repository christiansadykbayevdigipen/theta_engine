#pragma once 

#include "core.h"

typedef enum {
    THETA_TEXTURE_WRAP_TYPE_CLAMP,
    THETA_TEXTURE_WRAP_TYPE_REPEAT,
    THETA_TEXTURE_WRAP_TYPE_MIRROR,
    THETA_TEXTURE_WRAP_TYPE_MIRROR_CLAMP_TO_EDGE
}theta_texture_wrap_type;

typedef struct theta_texture {
    void* uninterpreted_data;
}theta_texture;

THETA_API theta_texture* theta_texture_init(const char* filepath);
THETA_API theta_texture* theta_texture_initw(const char* filepath, theta_texture_wrap_type wrap_type);