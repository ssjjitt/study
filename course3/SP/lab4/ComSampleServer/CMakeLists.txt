cmake_minimum_required(VERSION 3.20)

project(ComSampleServer CXX)
include_directories(../ComSampleProxy ../ComSampleService)
add_library(
    ComSampleServer
    SHARED
    Dll.cpp
    ClassFactory.cpp
    CComServerTest.cpp
)

target_link_options(ComSampleServer PRIVATE 
        /DEF:${CMAKE_CURRENT_SOURCE_DIR}/ComSampleServer.def
)

target_link_libraries(ComSampleServer Shlwapi)
set_source_files_properties(ComSampleServer.def PROPERTIES HEADER_FILE_ONLY TRUE)

add_custom_command(
    TARGET ComSampleServer
    POST_BUILD
    COMMAND "regsvr32" ARGS $<TARGET_FILE:ComSampleServer>
    VERBATIM
)