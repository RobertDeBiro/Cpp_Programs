# Set minimum CMake version
cmake_minimum_required(VERSION 3.24.1)

# Establish the name of the project
project(CMake_Tutorial1)

# Set variable "EXEVAR" to value "Embedded"
set(EXEVAR Adder_and_GLFW_lib)

# Create Embedded.exe by building main.cpp
#  - Embedded.exe i.e. EXEVAR becomes target for following part of CMakeLists.txt
add_executable(${EXEVAR} main.cpp)

# Download all the submodules
find_package(Git)
if(Git_FOUND AND EXISTS "../../.git")
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Submodule update")
        execute_process(
            COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            RESULT_VARIABLE GIT_SUBMOD_RESULT    
        )
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init failed with $(GIT_SUBMOD_RESULT)")
        endif()
    endif()
endif()

# Add a subdirectories to the build
# - subdirectories must contain CMakeLists.txt
# - when this CMake is executed, CMakes from subdirectories will be also executed
add_subdirectory(Adder)
add_subdirectory(external/glfw)

# When compiling, search for files inside included directory
#  - with this, in main.cpp, we don't have to use #include "Adder/adder.h", adder.h is enough
target_include_directories(${EXEVAR}
    PUBLIC Adder
    PUBLIC external/glfw/include
)

# Specify that, when started linking with source files, flags adder and glfw3 will be linked:
#  - those flags are created as part of add_library command, and 
#    represent real libraries: libadder.a, libglfw3.a
target_link_libraries(${EXEVAR} adder glfw)
