#pragma once

#include "core.h"
#include "math/tmath.h"

// TODO: Move rotation to a quaternion system.
typedef struct {
    theta_vector3f position;
    theta_vector3f rotation;
    theta_vector3f scale;
}theta_transform;