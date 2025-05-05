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

/*Boolean Type*/
typedef int BOOL;

typedef enum {
    THETA_LOGGER_SEVERITY_FATAL,
    THETA_LOGGER_SEVERITY_ERROR,
    THETA_LOGGER_SEVERITY_WARNING,
    THETA_LOGGER_SEVERITY_INFO,
    THETA_LOGGER_SEVERITY_DEBUG,
    THETA_LOGGER_SEVERITY_TRACE
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

#define THETA_FATAL(X, ...) theta_logger_log(THETA_LOGGER_SEVERITY_FATAL, X, ##__VA_ARGS__)
#define THETA_ERROR(X, ...) theta_logger_log(THETA_LOGGER_SEVERITY_ERROR, X, ##__VA_ARGS__)
#define THETA_WARN(X, ...) theta_logger_log(THETA_LOGGER_SEVERITY_WARNING, X, ##__VA_ARGS__)
#define THETA_INFO(X, ...) theta_logger_log(THETA_LOGGER_SEVERITY_INFO, X, ##__VA_ARGS__)
#define THETA_DEBUG(X, ...) theta_logger_log(THETA_LOGGER_SEVERITY_DEBUG, X, ##__VA_ARGS__)

#if defined(_WIN32) || defined(WINDOWS) || defined(__POSIX__) || defined(__LINUX__) || defined(__APPLE__)
#define THETA_PLATFORM_SHARED
#else
#error You're platform is not supported
#endif

// This macro is very useful when platform/api specific information exists. If you have a struct that has a void* uninterpreted data, this macro will cast that to the type you wish.
#define DATA_CAST(TYPE, VAR) ((TYPE*)VAR->uninterpreted_data)

typedef enum {
    THETA_API_OPENGL,
    THETA_API_NONE
}theta_api;

// This macro is useful for general malloc operations with structs.
#define INIT_STRUCT(TYPE) (TYPE*)(malloc(sizeof(TYPE)))