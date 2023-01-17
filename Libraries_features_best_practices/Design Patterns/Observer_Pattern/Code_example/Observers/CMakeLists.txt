set(lib_name Observers)

add_library(${lib_name} STATIC
    src/PhoneDisplay.cpp
    src/WindowsDisplay.cpp
)

target_include_directories(${lib_name}
    PUBLIC
        ${CMAKE_SOURCE_DIR}/Observers/inc
)