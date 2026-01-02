cmake_minimum_required(VERSION 3.28)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/out)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/out)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/out)

add_executable(Lab-03b-im main.c)
include_directories(${CMAKE_SOURCE_DIR}/GDVDLib/include)
link_directories(${CMAKE_SOURCE_DIR}/build/out)
target_link_libraries(Lab-03b-im PRIVATE GDVDLib)
