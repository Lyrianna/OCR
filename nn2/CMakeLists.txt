cmake_minimum_required(VERSION 3.7)

project(nn2)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(nn2 networkV2.c networkV2.h)
target_link_libraries(SDL2Test ${SDL2_LIBRARIES})