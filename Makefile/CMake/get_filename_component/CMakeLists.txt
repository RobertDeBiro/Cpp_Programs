message(STATUS "*****************************************************")

cmake_minimum_required(VERSION 3.24.1)
project(Misc)

set(FILE_VAR /c/Users/Robert/Desktop/IT/Programs/VSCode/Cpp/Makefile_practice/CMake/Miscellaneous/filename.txt)
message(STATUS "Filename path: ${FILE_VAR}")

get_filename_component(VAR ${FILE_VAR} DIRECTORY)
message(STATUS "get_filename_component/DIRECTORY: ${VAR}")

get_filename_component(VAR ${FILE_VAR} NAME)
message(STATUS "get_filename_component/NAME: ${VAR}")

get_filename_component(VAR ${FILE_VAR} ABSOLUTE)
message(STATUS "get_filename_component/ABSOLUTE: ${VAR}")

get_filename_component(VAR ${FILE_VAR} REALPATH)
message(STATUS "get_filename_component/REALPATH: ${VAR}")