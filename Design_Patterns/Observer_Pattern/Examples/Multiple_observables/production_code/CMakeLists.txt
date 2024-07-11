cmake_minimum_required(VERSION 3.22.1)

project(AlarmManager)

file(GLOB_RECURSE SOURCE *.cpp *.h)

add_executable(AlarmManager ${SOURCE})

target_include_directories(AlarmManager PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include)
