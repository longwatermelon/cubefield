cmake_minimum_required(VERSION 3.20.5)
set(CMAKE_C_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(cubefield)

find_package(SDL2 CONFIG REQUIRED)

add_executable(cubefield
    src/main.c
    src/cubefield.h
    src/cubefield.c
    src/cube.h
    src/cube.c
)

target_link_libraries(cubefield PRIVATE SDL2::SDL2 SDL2::SDL2main)

