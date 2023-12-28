cmake_minimum_required(VERSION 3.18)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_LIST_DIR}/mingw-toolchain.cmake)
if (CMAKE_CURRENT_SOURCE_DIR EQUAL CMAKE_CURRENT_BINARY_DIR)
    message(FATAL_ERROR "cannot use same source and binary dir!")
endif()

project(IsaacSocket LANGUAGES CXX ASM)

file(GLOB files *.cpp *.hpp *.h *.S)
add_library(IsaacSocket SHARED)
set_target_properties(IsaacSocket PROPERTIES PREFIX "")
target_sources(IsaacSocket PRIVATE ${files})
target_include_directories(IsaacSocket PRIVATE include)

add_executable(IsaacSocketClient)
target_sources(IsaacSocketClient PRIVATE client/client.cpp)
target_include_directories(IsaacSocketClient PRIVATE include)
