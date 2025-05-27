#pragma once

#include "core.h"

typedef enum {
    THETA_RESOURCE_TYPE_BINARY,
    THETA_RESOURCE_TYPE_PLAIN_TEXT
}theta_resource_type;

typedef struct {
    u8* data;
    u32 length;
    theta_resource_type resource_type;
}theta_resource;

// Reads a file and turns it into a theta resource.
THETA_API void theta_resource_init(theta_resource* resource, const char* filename, theta_resource_type resource_type);

// Deallocates all memory associated with the resource structure.
THETA_API void theta_resource_destroy(theta_resource* resource);