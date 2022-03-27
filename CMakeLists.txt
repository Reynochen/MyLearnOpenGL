cmake_minimum_required(VERSION 3.22 FATAL_ERROR)

project(TestOpenGL)

file(
    GLOB
        cppSrc "src/*.cpp"
)

include_directories("${PROJECT_SOURCE_DIR}/include")

add_executable(${PROJECT_NAME} ${cppSrc})

set(CMAKE_BUILD_TYPE Release)
#target_link_options(${PROJECT_NAME} PUBLIC -mwindows)

set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(external/glfw)
target_link_libraries(${PROJECT_NAME} glfw)

add_subdirectory(external/glad)
target_link_libraries(${PROJECT_NAME} glad)