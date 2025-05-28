cmake_minimum_required(VERSION 3.11)

project(lambda)

include_directories(../theta/src)
link_directories(../build/theta)
link_libraries(-ltheta)
include_directories(../stb)
include_directories(../cglm/include)

add_executable(lambda src/main.c)