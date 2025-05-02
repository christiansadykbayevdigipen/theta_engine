cmake_minimum_required(VERSION 3.10)

project(sandbox)

link_directories(../../theta/build)

link_libraries(-ltheta -lopengl32)

include_directories(../../theta/src)

#message(STATUS "YES: " ${})
#target_link_libraries(libtheta.dll.a)

add_executable(sandbox main.c)