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
        "src/menu.h"
        "src/menu.cpp"
        "src/utils.h"
        "src/utils.cpp"
        "src/level.h"
        "src/level.cpp"
        "src/throwRound.h"
        "src/throwRound.cpp"
        "src/town_map.h"
        "src/town_map.cpp"
        "src/masher.h"
        "src/masher.cpp"
        "src/drinkMeter.h"
        "src/drinkMeter.cpp"
        "src/physicsTest.h"
        "src/physicsTest.cpp"
        "src/throwTest.h"
        "src/throwTest.cpp"
        "src/colliderHelpers.h"
        "src/colliderHelpers.cpp"
        "src/shop.h"
        "src/shop.cpp"
        "src/inventory.h"
        "src/inventory.cpp"
        "src/inventory_manager.h"
        "src/inventory_manager.cpp"
        "src/beer.h"
        "src/beer_effect.h"
        "src/beer_effect.cpp"
        "src/beer_registry.h"
        "src/beer_registry.cpp"
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})