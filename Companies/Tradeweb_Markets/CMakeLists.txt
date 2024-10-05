cmake_minimum_required(VERSION 3.10)
project(OrderCacheProject)

set(CMAKE_CXX_STANDARD 17)

# GoogleTest configuration
enable_testing()

# Include the header files
include_directories(include)

# Source files
add_executable(OrderCacheTest
    tests/OrderCacheTest.cpp
    source/OrderCache.cpp
)

# Link GoogleTest library
target_link_libraries(OrderCacheTest gtest gtest_main pthread)

# Add GoogleTest
add_test(NAME OrderCacheTest COMMAND OrderCacheTest)
