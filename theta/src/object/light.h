#pragma once

#include "core.h"
#include "transform.h"

typedef struct {
    vec3 location;
    vec3 color;
}theta_light;

typedef struct {
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
}theta_light_directional;