cmake_minimum_required(VERSION 3.11)

project(pi_project)

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

file(GLOB SOURCES
    "src/*.cpp"
    "src/*.h"
)

add_executable(main ${SOURCES})

target_link_libraries(main 
    raylib
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

target_include_directories(main PUBLIC "${raylib_SOURCE_DIR}/src")
