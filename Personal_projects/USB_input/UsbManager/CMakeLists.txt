cmake_minimum_required(VERSION 3.22.1)

project(Usb_prj)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)

add_executable(Usb_test main.cpp)

# Find "libusb" package and link it to build
find_package(PkgConfig REQUIRED)
pkg_check_modules(libusb REQUIRED IMPORTED_TARGET libusb-1.0)

target_include_directories(Usb_test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(Usb_test PUBLIC $<TARGET_PROPERTY:PkgConfig::libusb,INTERFACE_INCLUDE_DIRECTORIES>)

add_subdirectory(src)

target_link_libraries(Usb_test MediaManager PkgConfig::libusb)

#! Following worked, but PkgConfig::<package> syntax was used
# target_include_directories(Usb_test PUBLIC ${LIBUSB_INCLUDE_DIRS})

#! Following solution didn't work:
# target_link_libraries(Usb_test ${libusb_LIBRARY_DIRS}/libusb-1.0.so)
