cmake_minimum_required(VERSION 3.22.1)

project(libusb_prj)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)

add_executable(libusb_test Device_desc.cpp)
# add_executable(libusb_test Determine_usb_type.cpp)
# add_executable(libusb_test listdevs.c)

# Find "libusb" package and link it to build
find_package(PkgConfig REQUIRED)
pkg_check_modules(libusb REQUIRED IMPORTED_TARGET libusb-1.0)

target_include_directories(libusb_test PUBLIC $<TARGET_PROPERTY:PkgConfig::libusb,INTERFACE_INCLUDE_DIRECTORIES>)

target_link_libraries(libusb_test PkgConfig::libusb)
