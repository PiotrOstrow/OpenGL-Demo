cmake_minimum_required(VERSION 3.24)

file(GLOB_RECURSE SOURCES "*.c" "*.h")
add_library(glad STATIC ${SOURCES})

target_include_directories(glad PUBLIC include)
