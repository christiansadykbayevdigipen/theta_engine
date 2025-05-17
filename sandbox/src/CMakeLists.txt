cmake_minimum_required(VERSION 3.10)

project(sandbox)

# add_compile_options(
#   "-Wall" "-Wpedantic" "-Wextra" "-fexceptions"
#   "$<$<CONFIG:DEBUG>:-O0;-g3;-ggdb>"
# )

set(CMAKE_BUILD_TYPE Debug)

link_directories(../../theta/build)

link_libraries(-ltheta -lm)

include_directories(../../theta/src)

#message(STATUS "YES: " ${})
#target_link_libraries(libtheta.dll.a)

add_executable(sandbox main.c)