add_library(MediaManager MediaManager.cpp)

target_include_directories(MediaManager PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(MediaManager PUBLIC $<TARGET_PROPERTY:PkgConfig::libusb,INTERFACE_INCLUDE_DIRECTORIES>)

# Find boost package and include its files
# set(Boost_USE_MULTITHREAD ON)
# find_package(Boost 1.81.0 COMPONENTS log_setup log system thread json REQUIRED)
# target_include_directories(MediaManager PUBLIC ${Boost_INCLUDE_DIRS})
# target_link_libraries(MediaManager PUBLIC Boost::log_setup Boost::log Boost::system Boost::thread Boost::json)
