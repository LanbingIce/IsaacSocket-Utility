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

# link_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib)
if (WIN32)
    link_directories(${CMAKE_CURRENT_SOURCE_DIR}/libs/zlib)
endif()

file(GLOB files src/*.cpp src/*/*.cpp libs/*/*.cpp src/*.S)
add_library(IsaacSocket SHARED)
set_target_properties(IsaacSocket PROPERTIES PREFIX "")
target_sources(IsaacSocket PRIVATE ${files})
target_include_directories(IsaacSocket PRIVATE include libs)

# find_package(OpenSSL COMPONENTS Crypto SSL)
# if (NOT OPENSSL_FOUND)
#     include(FetchContent)
#     message(STATUS "Not using system OpenSSL, using built-in OpenSSL project instead.")
#     set(MAKE make CACHE STRING "" FORCE)
#     FetchContent_Declare(
#         OpenSSL
#             GIT_REPOSITORY https://github.com/jimmy-park/openssl-cmake
#             GIT_TAG        main
#             USES_TERMINAL_DOWNLOAD TRUE)
#     FetchContent_MakeAvailable(OpenSSL)
# endif()
# target_link_libraries(IsaacSocket PRIVATE OpenSSL::Crypto OpenSSL::SSL)

if (WIN32)
    target_link_libraries(IsaacSocket PRIVATE ws2_32 crypt32 bcrypt winmm zlibstatic)
endif()

add_executable(IsaacSocketClient)
target_sources(IsaacSocketClient PRIVATE client/client.cpp)
target_include_directories(IsaacSocketClient PRIVATE include libs)

add_dependencies(IsaacSocketClient IsaacSocket)
