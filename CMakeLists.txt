cmake_minimum_required(VERSION 3.31)
project(OpenGL-Demo)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(third_party)
add_subdirectory(application)
