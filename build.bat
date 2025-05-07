@echo off

rem Set D to your CMAKE Location
set D="C:\Program Files\CMake\bin\cmake.exe"

rem Set F to your C Compiler Location
set F="C:\MinGW\bin\gcc.exe"

%D% -G "MinGW Makefiles" -D CMAKE_C_COMPILER=C:\MinGW\bin\gcc.exe -D CMAKE_BUILD_TYPE=Debug -S theta/src -B theta/build

cd theta
cd build
mingw32-make
cd ..
cd ..

%D% -G "MinGW Makefiles" -D CMAKE_C_COMPILER=C:\MinGW\bin\gcc.exe -D CMAKE_BUILD_TYPE=Debug -S sandbox/src -B sandbox/build

cd sandbox
cd build
mingw32-make
cd ..
cd ..

copy "%CD%\theta\build\libtheta.dll" "%CD%\sandbox\build\libtheta.dll"
del "%CD%\sandbox\build\res\*.*"
xcopy "%CD%\res" "%CD%\sandbox\build\res" /s /e /h /I