cmake_minimum_required(VERSION 3.24.1)

set(This Example)

project(${This} C CXX)

# Set variables that help the build system generator knows what version of
# programming language is used
set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)

# Setting for libraries that are going to be linked together into executables
set(CMAKE_POSITION_INDEPENDEND_CODE ON)

# Notify CMake that unit test will be used for current directory and below
enable_testing()

add_subdirectory(googletest)

# Set variables that contains name of the files that will be build
set(Headers
    Example.hpp
)

set(Sources
    Example.cpp
)

# The code that is going to be tested is following library
add_library(${This} STATIC ${Sources} ${Headers})

# Set property on target "Example" that it's linker language will be CXX (C++)
#  - normally the language is computed from the language of the source files listed in the target
#  - but, in this example, add_library uses variables rather then exact name of the files,
#    hence it cannot immediatelly deduce file type (.cpp) and cannot now the language of the source file
#  - when running cmake without this command, following error appears:
#       CMake Error: Cannot determine link language for target "Example".
#  - if we would use add_library command in following manner -
#    add_library(${This} STATIC Example.cpp Example.hpp) - no error would appear
# More info:
#  - Cannot determine link language for target:
#    https://cmake.org/pipermail/cmake/2006-July/010380.html
#  - CMake unable to determine linker language with C++:
#    https://stackoverflow.com/questions/11801186/cmake-unable-to-determine-linker-language-with-c
set_target_properties(${This} PROPERTIES LINKER_LANGUAGE CXX)

# The test that will test the code (the library)
add_subdirectory(test)