cmake_minimum_required(VERSION 3.31)

file(GLOB_RECURSE SOURCES "*.cpp" "*.h")

add_executable(opengl_demo ${SOURCES})
target_include_directories(opengl_demo PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

set_target_properties(opengl_demo PROPERTIES OUTPUT_NAME "OpenGL_Demo")

target_link_libraries(opengl_demo PRIVATE glad)
target_link_libraries(opengl_demo PRIVATE glfw)
target_link_libraries(opengl_demo PRIVATE glm)
target_link_libraries(opengl_demo PRIVATE tinyobjloader)
