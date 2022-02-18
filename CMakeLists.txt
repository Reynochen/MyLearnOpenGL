cmake_minimum_required(VERSION 3.22 FATAL_ERROR)

project(OpenGLTest)

add_executable(${PROJECT_NAME} src/main.cpp)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(external/glfw)
target_link_libraries(${PROJECT_NAME} glfw)
#For hide console in Windows
target_link_options(${PROJECT_NAME} PUBLIC -mwindows)