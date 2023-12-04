cmake_minimum_required(VERSION 3.10)

project(game VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS True)


add_subdirectory(../Engine ../Engine/build)

add_executable(game main.cpp)

target_link_libraries(game PRIVATE engine)
