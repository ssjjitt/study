cmake_minimum_required(VERSION 3.20)

project(ComSampleService CXX)
include_directories(../ComSampleProxy ../ComSampleServer)
add_executable(
    ComSampleService
    ClassFactory.cpp
    CComServiceTest.cpp
    Register.cpp
    Service.cpp
    Main.cpp
)

target_link_libraries(ComSampleService Shlwapi)

add_custom_command(
    TARGET ComSampleService
    POST_BUILD
    COMMAND $<TARGET_FILE:ComSampleService> ARGS "/RegisterServer"
    VERBATIM
)