cmake_minimum_required(VERSION 3.10)
project(theta)

add_compile_options(
  "-Wall" "-Wpedantic" "-Wextra" "-fexceptions"
  "$<$<CONFIG:DEBUG>:-O0;-g3;-ggdb>"
)

set(CMAKE_C_STANDARD 11)

find_package(glfw3 REQUIRED)

# Stole this line from Chat-GPT LOL
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(../../glfw/include)
include_directories(../include)
link_directories(../../glfw_build/src)
link_libraries(-lglfw3 -lm -lGL)

add_definitions(-D_GLFW_WIN32)

#FILE(GLOB GLFWCSources ../../glfw/src/*.c)
FILE(GLOB_RECURSE ThetaSources ${CMAKE_CURRENT_SOURCE_DIR}/*.c)

#add_library(theta SHARED ../../glfw/src/context.c ../../glfw/src/egl_context.c ../../glfw/src/glx_context.c ../../glfw/src/init.c ../../glfw/src/input.c ../../glfw/src/monitor.c ../../glfw/src/platform.c ../../glfw/src/wgl_context.c ../../glfw/src/win32_init.c ../../glfw/src/win32_joystick.c ../../glfw/src/win32_module.c ../../glfw/src/win32_monitor.c ../../glfw/src/win32_thread.c ../../glfw/src/win32_time.c ../../glfw/src/win32_window.c ../../glfw/src/vulkan.c ../../glfw/src/window.c logger/logger.c application/application.c )
#add_library(theta SHARED logger/logger.c application/application.c window/window.c window/platform/shared/shared_window.c)
add_library(theta SHARED ${ThetaSources} ../vendor/glad.c)