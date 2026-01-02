cmake_minimum_required(VERSION 3.28)

project(Lab03)

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
message("Win")
add_subdirectory(GDVLib)
add_subdirectory(Lab-03a)
add_subdirectory(GDVDLib)
add_subdirectory(GDVDLib++)
add_subdirectory(Lab-03b-Explicit)
add_subdirectory(Lab-03b-Implicit)

elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
message("Linux")
add_subdirectory(GDVLib)
add_subdirectory(Lab-03a)
add_subdirectory(LibGDVd)
add_subdirectory(Lab-03c)
endif()

