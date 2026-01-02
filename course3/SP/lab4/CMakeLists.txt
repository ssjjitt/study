cmake_minimum_required(VERSION 3.20)

project(COM C CXX)

set(LIBRARY_OUTPUT_PATH "${CMAKE_BINARY_DIR}")
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}")

add_subdirectory(ComSampleProxy)
add_subdirectory(ComSampleServer)
add_subdirectory(ComSampleService)
add_subdirectory(ComSampleClient)