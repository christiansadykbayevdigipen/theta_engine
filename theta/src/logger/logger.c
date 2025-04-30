#include "core.h"

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <memory.h>

void theta_logger_log(theta_logger_severity severity, const char* message, ...){
    char buffer[1024];
    memset(buffer, 0, 1024);
    switch(severity) {
    case THETA_LOGGER_SEVERITY_FATAL:
        strcat_s(buffer, 1024, "[Theta Fatal Error]: ");
        break;
    case THETA_LOGGER_SEVERITY_ERROR:
        strcat_s(buffer, 1024, "[Theta Error]: ");
        break;
    case THETA_LOGGER_SEVERITY_WARNING:
        strcat_s(buffer, 1024, "[Theta Warning]: ");
        break;
    case THETA_LOGGER_SEVERITY_INFO:
        strcat_s(buffer, 1024, "[Theta Info]: ");
        break;
    case THETA_LOGGER_SEVERITY_DEBUG:
        strcat_s(buffer, 1024, "[Theta Debug Log]: ");
        break;
    }
    
    va_list(args);
    va_start(args, message);

    printf(buffer);

    vprintf(message, args);
}