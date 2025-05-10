#include "core.h"

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <memory.h>
#include <assert.h>

void theta_logger_log(theta_logger_severity severity, const char* message, ...){
    char buffer[1024];
    memset(buffer, 0, 1024);
    switch(severity) {
    case THETA_LOGGER_SEVERITY_FATAL:
        strcat(buffer, "[Theta Fatal Error]: ");
        break;
    case THETA_LOGGER_SEVERITY_ERROR:
        strcat(buffer, "[Theta Error]: ");
        break;
    case THETA_LOGGER_SEVERITY_WARNING:
        strcat(buffer, "[Theta Warning]: ");
        break;
    case THETA_LOGGER_SEVERITY_INFO:
        strcat(buffer, "[Theta Info]: ");
        break;
    case THETA_LOGGER_SEVERITY_DEBUG:
        strcat(buffer, "[Theta Debug Log]: ");
        break;
    case THETA_LOGGER_SEVERITY_TRACE:
        strcat(buffer, "[Theta Trace]: ");
        break;
    default:
        strcat(buffer, "[Unknown Logging Severity]: ");
        break;
    }
    
    va_list(args);
    va_start(args, message);

    printf(buffer);

    vprintf(message, args);

    if(severity == THETA_LOGGER_SEVERITY_FATAL)
    {
        assert(!"Theta engine had to terminate because it ran into a fatal error.");
    }
}