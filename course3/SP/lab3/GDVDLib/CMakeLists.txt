cmake_minimum_required(VERSION 3.28)

project(GDVDLib C)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/out)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/out)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/out)

add_library(GDVDLib SHARED binary_search.c dllmain.c)
target_include_directories(GDVDLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
set_target_properties(GDVDLib PROPERTIES LINK_FLAGS "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/GDVDLib.def")