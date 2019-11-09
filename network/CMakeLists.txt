cmake_minimum_required(VERSION 3.15)
project(network)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(network
    .idea/.gitignore
    .idea/misc.xml
    .idea/modules.xml
    .idea/network.iml
    .idea/vcs.xml
    .idea/workspace.xml
    main.c
    xor_network.c
    xor_network.h)
