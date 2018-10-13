cmake_minimum_required(VERSION 3.8)

project(SandGame)

set(CMAKE_SKIP_BUILD_RPATH 0)
set(CMAKE_BUILD_WITH_INSTALL_RPATH 0)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin/")
set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "-Wall -Wpedantic -Wextra")

file(GLOB_RECURSE SOURCES src/*.cpp src/*.hpp)
include_directories("src/")

add_executable(
    SandGame
    ${SOURCES}
)

target_link_libraries(
    SandGame
    allegro
    allegro_primitives
    allegro_image
    allegro_font
    allegro_ttf
)
