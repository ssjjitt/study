cmake_minimum_required(VERSION 3.20)

project(ComSampleClient CXX)

include_directories(../ComSampleProxy ../ComSampleService ../ComSampleServer)
add_executable(Client Main.cpp)