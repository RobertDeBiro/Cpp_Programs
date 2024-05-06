pkg_check_modules(libusb REQUIRED IMPORTED_TARGET libusb-1.0)
# include_directories(PUBLIC $<TARGET_PROPERTY:PkgConfig::libusb,INTERFACE_INCLUDE_DIRECTORIES>)
include_directories(${libusb_INCLUDE_DIRS})

target_link_libraries(rtkplanning ${libusb_LIBRARIES})
# target_link_libraries(rtkplanning PkgConfig::libusb)