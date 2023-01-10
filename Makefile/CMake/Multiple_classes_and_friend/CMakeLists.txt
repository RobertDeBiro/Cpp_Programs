message(STATUS "*****************************************************")

cmake_minimum_required(VERSION 3.24.1)
project(Multiple_classes_and_friend_prj)

# add_executable(Multiple_classes_and_friend
#     main.cpp
#     Point3d/Point3d.cpp
#     Vector3d/Vector3d.cpp
# )

add_executable(Multiple_classes_and_friend
    main.cpp
)

# WE OBTAIN AN ERROR SINCE DIRECTORIES ARE NOT INCLUDED IN OTHER TARGETS
# Include Point3d and Vector3d directories to a target (to Multiple_classes_and_friend.exe)
# target_include_directories(Multiple_classes_and_friend
#     PUBLIC Point3d
#     PUBLIC Vector3d
# )

# Include Point3d and Vector3d directories to the build
include_directories(Point3d Vector3d)

# Targets from sub-directories must be defined after this command
# - targets from sub-directories are created with add_subdirectory()
#add_definitions(-DRANDOM_MACRO_VAL=1000 -DRANDOM_MACRO)
add_compile_definitions(RANDOM_MACRO_VAL=1000 RANDOM_MACRO)

add_subdirectory(Point3d)
add_subdirectory(Vector3d)

#target_link_libraries(Multiple_classes_and_friend Point3d Vector3d)
# FOLLOWING DOESN'T WORK, DON'T KNOW WHY!
# target_link_directories(Multiple_classes_and_friend
#     PUBLIC out/build/Point3d 
#     PUBLIC out/build/Vector3d
# )

message(STATUS "CMAKE_BINARY_DIR = ${CMAKE_BINARY_DIR}")
message(STATUS "CMAKE_SOURCE_DIR = ${CMAKE_SOURCE_DIR}")
message(STATUS "CMAKE_LIBRARY_OUTPUT_DIRECTORY = ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")

message(STATUS "*****************************************************")