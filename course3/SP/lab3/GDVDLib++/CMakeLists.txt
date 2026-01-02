cmake_minimum_required(VERSION 3.28)

project(GDVDLib++ CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/out)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/out)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/out)

add_library(GDVDLib++ SHARED binary_search.cpp dllmain.cpp)
target_include_directories(GDVDLib++ PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
