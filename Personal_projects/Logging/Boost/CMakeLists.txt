cmake_minimum_required(VERSION 3.22.1)

project(Boost_Logging_Prj)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)

add_executable(Boost_Logging Boost_Logging.cpp)

# Find boost package and include its files
set(Boost_USE_MULTITHREAD ON)
find_package(Boost 1.81.0 COMPONENTS log_setup log system thread json REQUIRED)
target_include_directories(Boost_Logging PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(Boost_Logging PUBLIC Boost::log_setup Boost::log Boost::system Boost::thread Boost::json)
