#pragma once

#include <stdio.h>

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

#if defined(_WIN32)
#define EXPORT __declspec(dllexport)
#define IMPORT __declspec(dllimport)
#else
#define EXPORT __attribute__ ((dllexport))
#define IMPORT __attribute__ ((dllimport))
#endif

#if defined(THETA_BUILD_SHARED)
#define THETA_API
#else
#define THETA_API
#endif


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
#define THETA_TRACE(X, ...) theta_logger_log(THETA_LOGGER_SEVERITY_TRACE, X, ##__VA_ARGS__)

#if defined(_WIN32) || defined(WINDOWS) || defined(__POSIX__) || defined(__LINUX__) || defined(__APPLE__) || defined(__linux__) || defined(__posix__)
#define THETA_PLATFORM_SHARED
#else
#error Your platform is not supported
#endif

#if defined(_WIN32) || defined(WINDOWS)
#define THETA_PLATFORM_WIN32
#endif

#if defined(__POSIX__) || defined(__LINUX__) || defined(__APPLE__) || defined(__linux__) || defined(__posix__)
#define THETA_PLATFORM_POSIX
#endif

// This macro is very useful when platform/api specific information exists. If you have a struct that has a void* uninterpreted data, this macro will cast that to the type you wish.
#define DATA_CAST(TYPE, VAR) ((TYPE*)VAR->uninterpreted_data)

typedef enum {
    THETA_API_OPENGL,
    THETA_API_NONE
}theta_api;

// This macro is useful for general malloc operations with structs.
#define INIT_STRUCT(TYPE) (TYPE*)(malloc(sizeof(TYPE)))

#define THETA_ASSERT(STATEMENT, MESSAGE) if(!STATEMENT) THETA_FATAL("Theta has ran into a failed assertion! Statement: %s, Message: %s\n", #STATEMENT, MESSAGE)

//https://stackoverflow.com/questions/15305310/predefined-macros-for-function-name-func
#ifndef __FUNCTION_NAME__
    #ifdef WIN32   //WINDOWS
        #define __FUNCTION_NAME__   __FUNCTION__  
    #else          //*NIX
        #define __FUNCTION_NAME__   __func__ 
    #endif
#endif

#define THETA_PROFILE() THETA_TRACE("%s\n", __FUNCTION_NAME__)

// Honestly, I loved the way that Hazel does this. Sooo... Basically copied and pasted it into my engine
// But here's the credit: https://github.com/TheCherno/Hazel/blob/master/Hazel/src/Hazel/Core/Base.h
// Hazel is made by Yan Chernikov.
#include <memory>
#include <utility>

namespace theta
{
    template <typename T>
    using Scope = std::unique_ptr<T>;
    template<typename T, typename ... Args>
    constexpr Scope<T> CreateScope(Args&& ... args)
    {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }

    template <typename T>
    using Ref = std::shared_ptr<T>;
    template<typename T, typename ... Args>
    constexpr Ref<T> CreateRef(Args&& ... args)
    {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }
}