cmake_minimum_required(VERSION 3.10)
project(theta)

# Stole this line from Chat-GPT LOL
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_library(theta SHARED logger/logger.c application/application.c)