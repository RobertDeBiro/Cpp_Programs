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