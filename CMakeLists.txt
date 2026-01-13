cmake_minimum_required(VERSION 3.11)

project(
    pi_project
    VERSION 1.0
    LANGUAGES CXX
)

find_package(raylib 5.5 QUIET)

# This code downloads raylib into a directory called _deps and adds it as a subdirectory, compiling it with the program when running the build command
include(FetchContent)
if (NOT raylib_FOUND)
    FetchContent_Declare(
        raylib
        URL https://github.com/raysan5/raylib/archive/refs/tags/5.5.tar.gz
        DOWNLOAD_EXTRACT_TIMESTAMP True #This option is not required but suppresses a warning
    )
    FetchContent_MakeAvailable(raylib)
endif()

set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

link_libraries(raylib)

include_directories(
    PUBLIC
        "${raylib_SOURCE_DIR}/src"
)

add_executable(main)

target_sources(main
    PRIVATE
        "src/main.cpp"
        "src/physObj.cpp"
        "src/physObj.h"
        "src/projectile.cpp"
        "src/projectile.h"
        "src/target.cpp"
        "src/target.h"
)

add_executable(PhysicsTest)

target_sources(PhysicsTest
    PRIVATE
        "src/physicsTest.cpp"
        "src/physObj.cpp"
        "src/physObj.h"
        "src/projectile.cpp"
        "src/projectile.h"
        "src/target.cpp"
        "src/target.h"
)

add_executable(ThrowTest)

target_sources(ThrowTest
    PRIVATE
        "src/throwTest.cpp"
        "src/physObj.cpp"
        "src/physObj.h"
        "src/projectile.cpp"
        "src/projectile.h"
        "src/target.cpp"
        "src/target.h"
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})