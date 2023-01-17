message(STATUS "*****************************************************")

function(open_notepad)
    message(STATUS "Opening readme.md in notepad++")
    execute_process(
        COMMAND notepad++ readme.md
        RESULT_VARIABLE README_ID
    )
endfunction()

cmake_minimum_required(VERSION 3.24.1)

# include files/modules
include(CMakePrintHelpers) # cmake_print_variables

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/custom_modules)
cmake_print_variables(CMAKE_MODULE_PATH)
message(STATUS "CMAKE_MODULE_PATH = ${CMAKE_MODULE_PATH}")
include(custom_funct_module) # add_exec_src_file

project(Adding_two_integers_prj)

add_exec_src_file()
target_include_directories(Adding_two_integers PUBLIC IO)

#open_notepad()

message(STATUS "*****************************************************\n")