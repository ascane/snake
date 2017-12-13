cmake_minimum_required (VERSION 3.1)

project (Snake)

set (CMAKE_CXX_STANDARD 11)
include_directories("${PROJECT_BINARY_DIR}")
add_executable(Snake main.cpp)

