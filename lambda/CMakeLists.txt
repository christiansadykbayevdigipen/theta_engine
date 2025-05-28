cmake_minimum_required(VERSION 3.11)
project(lambda)

set(CMAKE_CXX_STANDARD 20)


include_directories(../theta/src)
include_directories(../cglm/include)

link_directories(../build/theta)

link_libraries(-ltheta)

add_executable(lambda src/main.cpp)