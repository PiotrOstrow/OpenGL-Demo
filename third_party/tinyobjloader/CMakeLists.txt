cmake_minimum_required(VERSION 3.31)

add_library(tinyobjloader include/tiny_obj_loader.h src/tiny_obj_loader.cpp)
target_include_directories(tinyobjloader PUBLIC include)
