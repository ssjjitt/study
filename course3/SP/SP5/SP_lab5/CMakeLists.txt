cmake_minimum_required(VERSION 3.20) 
project(SP_lab5 LANGUAGES C)

find_program(CLANG_EXECUTABLE clang)
if(NOT CLANG_EXECUTABLE)
    message(FATAL_ERROR "Clang compiler (clang) not found. Please install Clang or ensure it's in your PATH.")
else()
    message(STATUS "Using Clang C compiler: ${CLANG_EXECUTABLE}")
    set(CMAKE_C_COMPILER "${CLANG_EXECUTABLE}")
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

message(STATUS "Output directory for executables: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")

if(WIN32)
    message(STATUS "Configuring for Windows")
    add_subdirectory(DemoService)
    add_subdirectory(ServiceCtl)

elseif(UNIX AND NOT APPLE)
    message(STATUS "Configuring for Linux")
    add_subdirectory(demoserviced)
else()
    message(WARNING "Unsupported OS configuration. Only Windows and Linux are fully supported by this project.")
endif()

message(STATUS "Root CMake configuration finished.")