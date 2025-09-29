add_executable(DemoService DemoService.c)

target_link_libraries(DemoService PRIVATE Advapi32 shlwapi)

message(STATUS "Configured DemoService target for Windows.")

set(CONFIG_SOURCE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/config.ini") 

if(NOT EXISTS "${CONFIG_SOURCE_PATH}")
    message(WARNING "Source config file not found at ${CONFIG_SOURCE_PATH}")
else()
    add_custom_command(TARGET DemoService POST_BUILD
                       COMMAND ${CMAKE_COMMAND} -E copy_if_different
                       "${CONFIG_SOURCE_PATH}"
                       $<TARGET_FILE_DIR:DemoService>/config.ini
                       COMMENT "Copying config.ini next to executable"
                       VERBATIM)
    message(STATUS "Added post-build step to copy ${CONFIG_SOURCE_PATH} next to DemoService.exe")
endif()