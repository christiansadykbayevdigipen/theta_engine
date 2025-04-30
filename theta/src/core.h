#pragma once

/*Unsigned types*/
typedef unsigned long u64;
typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;

/*Signed types*/
typedef signed long s64;
typedef signed int s32;
typedef signed short s16;
typedef signed char s8;

/*Float types*/
typedef float f32;
typedef double f64;
typedef long double f80;

typedef enum {
    THETA_LOGGER_SEVERITY_FATAL,
    THETA_LOGGER_SEVERITY_ERROR,
    THETA_LOGGER_SEVERITY_WARNING,
    THETA_LOGGER_SEVERITY_INFO,
    THETA_LOGGER_SEVERITY_DEBUG
}theta_logger_severity;

#define THETA_API extern
#define MAX_STRING 512
#define TRUE 1
#define FALSE 0

/*
@brief This is Theta's logger.
@param severity This specifies how serious the log will show up in the console
@param message This is the message that you wish to log
@param ... These are optional arguments that you can include into the message. This works exactly like printf.
*/
THETA_API void theta_logger_log(theta_logger_severity severity, const char* message, ...);