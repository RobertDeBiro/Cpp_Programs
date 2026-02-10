cmake_minimum_required(VERSION 3.20)

project(IteratorAndComposite
    VERSION 1.0
    DESCRIPTION "Iterator and Composite Patterns Implementation"
    LANGUAGES CXX
)

# Set C++20 standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# SonarQube compliance: Enable all warnings and treat them as errors
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(
        -Wall                    # Enable all standard warnings
        -Wextra                  # Enable extra warnings
        -Werror                  # Treat warnings as errors
        -pedantic                # Enforce ISO C++ compliance
        -Wshadow                 # Warn on variable shadowing
        -Wnon-virtual-dtor      # Warn on non-virtual destructors
        -Wold-style-cast        # Warn on C-style casts
        -Wcast-align            # Warn on pointer cast alignment
        -Wunused                # Warn on unused entities
        -Woverloaded-virtual    # Warn on overloaded virtuals
        -Wpedantic              # Warn on non-standard C++
        -Wconversion            # Warn on type conversions
        -Wsign-conversion       # Warn on sign conversions
        -Wformat=2              # Warn on format string issues
        -Wno-unknown-pragmas    # Don't warn on unknown pragmas
    )
elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    add_compile_options(
        /W4                     # Warning level 4
        /WX                     # Treat warnings as errors
        /permissive-            # Standards conformance
    )
endif()

# Include directories
include_directories(${CMAKE_SOURCE_DIR})

# Source files
set(SOURCES
    main.cpp
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Output directory for executable
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
)

# Print configuration info
message(STATUS "Project: ${PROJECT_NAME}")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Compiler: ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")
