cmake_minimum_required(VERSION 3.16)

project(MediaPlayer C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

add_executable(MonPG1 MonPG1.c)

if(MSVC)
    target_compile_options(MonPG1 PRIVATE /W4)
else()
    target_compile_options(MonPG1 PRIVATE -Wall -Wextra -Wpedantic)
endif()
