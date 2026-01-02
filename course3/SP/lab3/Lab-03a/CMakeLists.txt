cmake_minimum_required(VERSION 3.28)

project(Lab-03a C)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/out)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/out)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/out)

add_executable(Lab-03a main.c)
target_link_libraries(Lab-03a PRIVATE GDVLib)
target_include_directories(Lab-03a PRIVATE ../GDVLib)
