cmake_minimum_required(VERSION 3.20)
project(SingletonPattern VERSION 1.0 LANGUAGES CXX)

# C++20 standard required
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Compiler warnings (SonarQube compliant)
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-Wall -Wextra -Wpedantic -Werror)
endif()

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/inc)

# Source files - only main.cpp (header-only pattern)
set(SOURCES
    main.cpp
)

# Create executable
add_executable(singleton_pattern ${SOURCES})

# Link pthread for thread support
find_package(Threads REQUIRED)
target_link_libraries(singleton_pattern PRIVATE Threads::Threads)

# Set output directory
set_target_properties(singleton_pattern PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out/build
)

# Print configuration
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Compiler: ${CMAKE_CXX_COMPILER_ID}")
