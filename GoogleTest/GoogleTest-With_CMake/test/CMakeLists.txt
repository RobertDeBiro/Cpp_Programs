cmake_minimum_required(VERSION 3.24.1)

set(This ExampleTests)

set(Sources
    ExampleTests.cpp
)

# Create the program itself
add_executable(${This} ${Sources})

target_link_libraries(${This} PUBLIC
    gtest_main
    Example
)

# Saying that this file is a test that can be run with ctest
add_test(
    NAME ${This}
    COMMAND ${This}
)