cmake_minimum_required(VERSION 3.22.1)
project(CreateDirProject)

add_executable(CreateDirProject main.cpp)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    # Generate a timestamp
    string(TIMESTAMP CURRENT_TIME "%d_%m_%Y-%H_%M_%S")

    # Pass the timestamp to the C++ code
    add_definitions(-DCURRENT_TIME="${CURRENT_TIME}")
endif()

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
