#pragma once

#include "core.h"
#include <cglm/cglm.h>

// TODO: Move rotation to a quaternion system.
typedef struct {
    vec3 position;
    vec3 rotation;
    vec3 scale;
}theta_transform;