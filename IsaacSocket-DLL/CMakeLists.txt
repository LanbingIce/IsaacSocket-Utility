cmake_minimum_required(VERSION 3.18)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_LIST_DIR}/mingw-toolchain.cmake)

project(IsaacSocket LANGUAGES CXX)

file(GLOB files *.cpp *.hpp *.h)
add_library(IsaacSocket SHARED ${files})
target_include_directories(IsaacSocket PRIVATE include)
