#include "resource.h"

#include <stdio.h>
#include <string.h>

void theta_resource_init(theta_resource* resource, const char* filename, theta_resource_type resource_type) {
    char reading_mode[20] = "r";

    if(resource_type != THETA_RESOURCE_TYPE_PLAIN_TEXT) {
        strcpy(reading_mode, "rb");
    }
    
    FILE* file_handle = fopen(filename, reading_mode);
    THETA_ASSERT(file_handle, "theta_resource_init has failed. The reason being, the filename that has been requested does not exist!\n");

    char c;
    while((c = getc(file_handle)) != EOF) {
        
    }

    fclose(file_handle);
}

void theta_resource_destroy(theta_resource* resource) {

}