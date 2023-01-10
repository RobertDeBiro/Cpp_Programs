# cmake-variables: https://cmake.org/cmake/help/latest/manual/cmake-variables.7.html

#########################################################################################
# CMAKE_MODULE_PATH
# - reference: https://cmake.org/cmake/help/latest/variable/CMAKE_MODULE_PATH.html
#########################################################################################
# Two ways of setting CMAKE_MODULE_PATH variable:
set(CMAKE_MODULE_PATH custom_modules)
list(APPEND CMAKE_MODULE_PATH custom_modules)


#########################################################################################
# CMAKE_BINARY_DIR and CMAKE_SOURCE_DIR
#  - reference: https://cmake.org/cmake/help/latest/variable/CMAKE_BINARY_DIR.html
#  - reference: https://cmake.org/cmake/help/latest/variable/CMAKE_SOURCE_DIR.html
#########################################################################################
message(STATUS "CMAKE_BINARY_DIR = ${CMAKE_BINARY_DIR}")
message(STATUS "CMAKE_SOURCE_DIR = ${CMAKE_SOURCE_DIR}")


#########################################################################################
# Print variables
#########################################################################################
# Include "CMakePrintHelpers" module that contains "cmake_print_variables"
# function for printing variables
include(CMakePrintHelpers) # cmake_print_variables

set(CMAKE_MODULE_PATH custom_modules)

cmake_print_variables(CMAKE_MODULE_PATH)
message(STATUS "CMAKE_MODULE_PATH = ${CMAKE_MODULE_PATH}")
