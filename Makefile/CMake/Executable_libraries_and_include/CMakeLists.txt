# Setting cmake depending on the installed version
# cmake_minimum_required(VERSION 3.26.3)
cmake_minimum_required(VERSION 3.22.1)

project(Multiple_classes_and_friend_prj)

add_executable(Multiple_classes_and_friend main.cpp)

# Compile definitions defined in source "CMakeLists.txt" must be defined before 
# adding subdirectory in which library that uses MACRO is created
# If it is defined after 'add_subdirectory', build would failed
#  - I don't know why is that, since when this command is placed inside 'add_subdirectory()'
#    it can be placed at the end
add_compile_definitions(RANDOM_MACRO_VAL=1000 RANDOM_MACRO)

add_subdirectory(Point3d)
add_subdirectory(Vector3d)

target_link_libraries(Multiple_classes_and_friend Point3d Vector3d)

set(CMAKE_MODULE_PATH custom_modules)