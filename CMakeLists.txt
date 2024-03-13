cmake_minimum_required(VERSION 3.24)
project(bonus)

set(CMAKE_CXX_STANDARD 17)

add_executable(bonus main.cpp)

# Copy distribution.txt file to build directory
configure_file(distribution.txt ${CMAKE_CURRENT_BINARY_DIR}/distribution.txt COPYONLY)
