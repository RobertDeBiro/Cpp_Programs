# Set minimum CMake version
#  - in order to see cmake version, in cmd type: cmake --version
cmake_minimum_required(VERSION 3.24.1)

# Set variable "This" to value "Embedded"
#  - command "set" sets a normal, cache, or environment variable to a given value
#  - in following example we are setting normal variable
#  - syntax:
#       set(<variable> <value>... [PARENT_SCOPE]) 
set(PrjVar Embedded)

# Establish the name of the project
#  - the name is retrieved from variable "PrjVar"
project(${PrjVar})

# Create the program itself, i.e. the executable
#  - we are building main.cpp into Embedded.exe
add_executable(${PrjVar} main.cpp)

# Add a subdirectory to the build
# - subdirectory must also contain CMakeLists.txt
# - that CMakeLists.txt contains command for building library
# - hence, the result of this command is that it adds command for building library into makefile
add_subdirectory(Adder)

# When compiling, search for files inside included directory
#  - with this, in main.cpp, we don't have to use #include "Adder/adder.h", adder.h is enough
target_include_directories(${PrjVar} PUBLIC Adder)

# Specify libraries or flags to use when linking a given target and/or its dependents
# - in this project we will use library "adder" from folder "Adder"
target_link_libraries(${PrjVar} adder)
