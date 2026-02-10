cmake_minimum_required(VERSION 3.20)
project(WeatherMonitoringObserver VERSION 1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Compiler warnings (SonarQube compliant)
if(MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -Wpedantic -Werror)
endif()

# Collect all source files
file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_LIST_DIR}/src/*.cpp)
set(SOURCES ${SOURCES} ${CMAKE_CURRENT_LIST_DIR}/main.cpp)

# Collect all header files for IDE support
file(GLOB_RECURSE HEADERS ${CMAKE_CURRENT_LIST_DIR}/inc/*.h)

# Executable
add_executable(weather_station ${SOURCES} ${HEADERS})

# Include directories
target_include_directories(weather_station PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/inc
)

# Installation
install(TARGETS weather_station DESTINATION bin)

# Display configuration
message(STATUS "")
message(STATUS "=== Observer Pattern - Weather Monitoring ===")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Compiler: ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "Source files: ${SOURCES}")
message(STATUS "=======================================")
message(STATUS "")
