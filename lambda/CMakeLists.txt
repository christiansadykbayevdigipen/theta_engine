cmake_minimum_required(VERSION 3.11)
project(lambda)

set(CMAKE_CXX_STANDARD 17)

include_directories(../theta/src)
include_directories(../cglm/include)
include_directories(../imgui)
include_directories(../glfw/include)

link_directories(../build/theta)

link_libraries(-ltheta)

add_executable(lambda src/main.cpp ../imgui/imgui.cpp ../imgui/imgui_widgets.cpp ../imgui/imgui_tables.cpp ../imgui/imgui_draw.cpp ../imgui/backends/imgui_impl_glfw.cpp ../imgui/backends/imgui_impl_opengl3.cpp)