#pragma once

#include "core.h"
#include "transform.h"

typedef struct {
    theta_transform transform;
    theta_vector3f light_color;
}theta_light_descriptor;

typedef struct {
    f32 ambient_strength;
    theta_vector3f light_color;
}theta_light_ambient_descriptor;