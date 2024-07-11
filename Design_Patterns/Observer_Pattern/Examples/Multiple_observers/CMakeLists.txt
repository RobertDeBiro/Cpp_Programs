cmake_minimum_required(VERSION 3.24.1)

project(Observer_Pattern)

add_subdirectory(
    #Observable
    Observers
)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} Observers)

set(lib_name Observers)

add_library(${lib_name} STATIC
    src/PhoneDisplay.cpp
    src/WindowsDisplay.cpp
)

target_include_directories(${lib_name}
    PUBLIC
        ${CMAKE_SOURCE_DIR}/Observers/inc
)