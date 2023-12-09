cmake_minimum_required(VERSION 3.10)

project(engine VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS True)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG")
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(dependencies/glfw)

add_library(engine SHARED src/engine.cpp src/mesh.cpp src/buffer.cpp src/shader.cpp src/log.cpp glad.c)


target_include_directories(engine
    PRIVATE ${PROJECT_SOURCE_DIR}/dependencies/include
    PUBLIC ${PROJECT_SOURCE_DIR}/dependencies/include/public
    INTERFACE ${PROJECT_BINARY_DIR} ${PROJECT_SOURCE_DIR}/src/include
)

target_link_Libraries(engine PUBLIC glfw)
target_link_options(engine PUBLIC -static-libstdc++ -g)


install(TARGETS engine
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib/engine )
