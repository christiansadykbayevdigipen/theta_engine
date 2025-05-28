#include "application/application.h"
#include "theta.h"

void lambda_start(theta_application* app) {

}

void lambda_update(theta_application* app, f64 elapsed) {
    
}

void lambda_terminate(theta_application* app) {
    
}

theta_application g_lambda;
theta_application_descriptor g_descriptor = {
    "Lambda, A Theta Game Engine Editor", 
    lambda_start, 
    lambda_update, 
    lambda_terminate, 
    THETA_API_OPENGL, 
    FALSE, 
    FALSE, 
    FALSE,
    TRUE
};

int main() {
    theta_application_init(&g_lambda, g_descriptor);
    theta_application_run(&g_lambda);
    theta_application_destruct(&g_lambda);
}