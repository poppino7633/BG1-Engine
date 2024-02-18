cmake_minimum_required(VERSION 3.10)

project(BG1 VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS True)
set(CMAKE_CXX_FLAGS_DEBUG "-g")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
add_subdirectory(../Engine ../Engine/build)

add_executable(BG1 src/main.cpp)

target_link_libraries(BG1 PRIVATE engine)
target_link_options(BG1 PRIVATE -g)
target_compile_options(BG1 PRIVATE -g)

add_custom_target(assets
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets)

add_dependencies(BG1 assets)

install(TARGETS BG1 
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib/game )

install(DIRECTORY assets 
        DESTINATION .)
