message(STATUS "*****************************************************")

# Setting cmake depending on the installed version
# cmake_minimum_required(VERSION 3.26.3)
cmake_minimum_required(VERSION 3.22.1)

project(Misc)

set(FILE_VAR /home/robert/IT/Programs/Cpp_Programs/Makefile/CMake/get_filename_component/filename.txt)
message(STATUS "Filename path: ${FILE_VAR}")

get_filename_component(VAR ${FILE_VAR} DIRECTORY)
message(STATUS "get_filename_component/DIRECTORY: ${VAR}")

get_filename_component(VAR ${FILE_VAR} NAME)
message(STATUS "get_filename_component/NAME: ${VAR}")

get_filename_component(VAR ${FILE_VAR} ABSOLUTE)
message(STATUS "get_filename_component/ABSOLUTE: ${VAR}")

get_filename_component(VAR ${FILE_VAR} REALPATH)
message(STATUS "get_filename_component/REALPATH: ${VAR}")