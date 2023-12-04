cmake_minimum_required(VERSION 3.10)

project(engine VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS True)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(dependencies/glfw)

add_library(engine STATIC src/engine.cpp src/mesh.cpp glad.c)

target_include_directories(engine
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src 
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/include
    INTERFACE ${PROJECT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/src/include
)

target_link_Libraries(engine PUBLIC glfw)
target_link_options(engine PUBLIC -static-libstdc++)

