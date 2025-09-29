cmake_minimum_required(VERSION 3.28)

project(GDVLib C)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/out)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/out)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/out)

add_library(GDVLib STATIC binary_search.c)
target_include_directories(GDVLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
