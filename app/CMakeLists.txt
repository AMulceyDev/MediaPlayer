cmake_minimum_required(VERSION 3.0)
project(MediaPlayer C)
add_executable(Billing Billing.c)
add_executable(change_calculator change_calculator.c)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

add_executable(LREmailCounter LREmailCounter.c)
target_include_directories(LREmailCounter PRIVATE ${GTK3_INCLUDE_DIRS})
target_compile_options(LREmailCounter PRIVATE ${GTK3_CFLAGS_OTHER})
target_link_libraries(LREmailCounter PRIVATE ${GTK3_LIBRARIES})

