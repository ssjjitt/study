cmake_minimum_required(VERSION 3.20)

project(ComSampleProxy)

get_filename_component(IDLNAME "IComTest.idl" NAME_WE)
set(OUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/Generated/)
make_directory(${OUT_DIR})
set(OUT_NAME ${OUT_DIR}/${IDLNAME})
list(APPEND IDL_COMPILED_FILES ${OUT_NAME}_i.c ${OUT_NAME}_p.c ${OUT_DIR}dlldata.c)

add_custom_command(
    OUTPUT ${IDL_COMPILED_FILES}
    COMMAND midl ARGS ${CMAKE_CURRENT_SOURCE_DIR}/IComTest.idl
    WORKING_DIRECTORY ${OUT_DIR}
)

add_library(ComSampleProxy SHARED "${IDL_COMPILED_FILES}")
target_compile_options(ComSampleProxy PRIVATE /DREGISTER_PROXY_DLL)
target_link_options(ComSampleProxy PRIVATE 
        /DEF:${CMAKE_CURRENT_SOURCE_DIR}/IComTest.def
)
target_link_libraries(ComSampleProxy kernel32 rpcns4 rpcrt4 uuid)

add_custom_command(
    TARGET ComSampleProxy
    POST_BUILD
    COMMAND "regsvr32" ARGS $<TARGET_FILE:ComSampleProxy>
    VERBATIM
)
