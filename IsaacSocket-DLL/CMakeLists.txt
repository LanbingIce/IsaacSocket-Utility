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

file(GLOB files src/*.cpp libs/*/*.cpp src/*.S)
add_library(IsaacSocket SHARED)
set_target_properties(IsaacSocket PROPERTIES PREFIX "")
target_sources(IsaacSocket PRIVATE ${files})
target_include_directories(IsaacSocket PRIVATE include libs)

if (UNIX)
    find_package(OpenSSL REQUIRED COMPONENTS Crypto SSL REQUIRED)
    target_link_libraries(main PRIVATE OpenSSL::Crypto OpenSSL::SSL)
elseif (WIN32)
    # target_link_libraries(IsaacSocket PRIVATE WS2_32 WSock32 crypt32 ssl_mingw32 crypto_mingw32)
    target_link_libraries(IsaacSocket PRIVATE ws2_32 crypt32)
endif()

add_executable(IsaacSocketClient)
target_sources(IsaacSocketClient PRIVATE client/client.cpp)
target_include_directories(IsaacSocketClient PRIVATE include libs)

add_dependencies(IsaacSocketClient IsaacSocket)
