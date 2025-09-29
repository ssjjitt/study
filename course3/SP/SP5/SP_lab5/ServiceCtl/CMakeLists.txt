add_executable(ServiceCtl ServiceCtl.c)

target_link_libraries(ServiceCtl PRIVATE Advapi32)

message(STATUS "Configured ServiceCtl target for Windows.")




