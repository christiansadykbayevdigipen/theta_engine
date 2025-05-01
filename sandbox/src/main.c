#include "../../theta/src/theta.h"

#include <string.h>
#include <stdio.h>

void sb_start() {

}

void sb_update(f64 elapsed_time) {

}

int main() {
    theta_application sandbox;
    theta_application_descriptor descriptor;
    strcpy_s(descriptor.app_name, MAX_STRING, "Sandbox");
    descriptor.start = sb_start;
    descriptor.update = sb_update;

    theta_application_init(&sandbox, descriptor);
    theta_application_run(&sandbox);
}