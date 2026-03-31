cmake_minimum_required(VERSION 4.1.0)
project(svDoom)

if(APPLE)
    set(MACOSX_BUNDLE ON)
endif()
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_subdirectory(vendor)
add_subdirectory(linuxdoom-1.10)