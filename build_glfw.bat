@echo off

rem Set D to your CMAKE Location
set D="C:\Program Files\CMake\bin\cmake.exe"

rem Set F to your C Compiler Location
set F="C:\MinGW\bin\gcc.exe"

%D% -G "MinGW Makefiles" -D CMAKE_C_COMPILER=%F% -S glfw -B glfw_build

cd glfw_build
mingw32-make