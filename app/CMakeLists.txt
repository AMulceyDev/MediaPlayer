cmake_minimum_required(VERSION 3.0)
project(MediaPlayer C)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/../cdRom")
add_executable(Billing Billing.c)
add_executable(change_calculator change_calculator.c)
add_executable(blackjack blackjack.c)
add_executable(compressFile compressFile.c)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

add_executable(LREmailCounter LREmailCounter.c)
target_include_directories(LREmailCounter PRIVATE ${GTK3_INCLUDE_DIRS})
target_compile_options(LREmailCounter PRIVATE ${GTK3_CFLAGS_OTHER})
target_link_libraries(LREmailCounter PRIVATE ${GTK3_LIBRARIES})

add_executable(MediaPlayer media_player.c)
target_include_directories(MediaPlayer PRIVATE ${GTK3_INCLUDE_DIRS})
target_compile_options(MediaPlayer PRIVATE ${GTK3_CFLAGS_OTHER})
target_link_libraries(MediaPlayer PRIVATE ${GTK3_LIBRARIES})

