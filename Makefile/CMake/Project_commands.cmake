# cmake-commands: https://cmake.org/cmake/help/latest/manual/cmake-commands.7.html

add_compile_definitions( # https://cmake.org/cmake/help/latest/command/add_compile_definitions.html
    
    # Add preprocessor definition to the compilation of source files
    #  - in this example we define a preprocessor variables (define a MACROs) that will be used inside every target
    #    in the current directory
    #  - MACROs: RANDOM_MACRO_VAL=1000, RANDOM_MACRO
    add_compile_definitions(RANDOM_MACRO_VAL=1000 RANDOM_MACRO)
)
#----------------------------------------------------------------------------------------------------------#
add_definitions( # https://cmake.org/cmake/help/latest/command/add_definitions.html"

    # Add -D define flags to the compilation of source files    
    #  - used to add any flags, but primarily intended to add preprocessor definitions
    #  - hence, following example is almost the same at example with add_compile_definitions()
    add_definitions(-DRANDOM_MACRO_VAL=1000 -DRANDOM_MACRO)

    # more info:
    # - https://stackoverflow.com/questions/45091722/cmake-add-definitions-does-not-seem-to-work
)
#----------------------------------------------------------------------------------------------------------#
add_executable( # https://cmake.org/cmake/help/latest/command/add_executable.html
    
    # Build executable "Hello_World" from main.cpp
    add_executable(Hello_World main.cpp)

    # Build executable "Adding_two_integers" from multiple files: main.cpp and io.cpp
    add_executable(Adding_two_integers main.cpp IO/io.cpp)

    # Build executable "Adding_two_integers" from multiple files: main.cpp and sources from IO directory
    aux_source_directory(./IO SRC)
    add_executable(Adding_two_integers main.cpp ${SRC})
)
#----------------------------------------------------------------------------------------------------------#
add_library( # https://cmake.org/cmake/help/latest/command/add_library.html
    
    # Create Vector3d library (Vector3d.a file) from Vector3d.cpp
    add_library(Vector3d Vector3d.cpp)
)
#----------------------------------------------------------------------------------------------------------#
add_test( # ttps://cmake.org/cmake/help/latest/command/add_test.html

    # Add a test called "Example_Test"
    add_test(
        NAME Example_Test
        COMMAND Example_Test # Specify test command-line as "Example_Test" target
    )
)
#----------------------------------------------------------------------------------------------------------#
aux_source_directory( # https://cmake.org/cmake/help/latest/command/aux_source_directory.html
    
    # Place every source file from IO directory, into variable "SRC"
    aux_source_directory(./IO SRC)
)
#----------------------------------------------------------------------------------------------------------#
add_subdirectory( # https://cmake.org/cmake/help/latest/command/add_subdirectory.html

    # Execute CMakeLists.txt from "Point3d" subdirectory
    add_subdirectory(Point3d)

    # - we can add directories that are not subdirectories by using a relative path
    add_subdirectory(../dir)
)
#----------------------------------------------------------------------------------------------------------#
enable_testing( # https://cmake.org/cmake/help/latest/command/enable_testing.html?highlight=enable_testing

    # Enable testing for current directory and below
    enable_testing()
)
#----------------------------------------------------------------------------------------------------------#
include_directories( # https://cmake.org/cmake/help/latest/command/include_directories.html
    
    # Include files from Point3d and Vector3d directories into every target
    # (.exe, .a, or .dll file) in current directory and in its subdirectories
    include_directories(Point3d Vector3d)
)
#----------------------------------------------------------------------------------------------------------#
project( # https://cmake.org/cmake/help/latest/command/project.html
    
    # Create project "Adding_two_integers_prj"
    #   - project creation sets "PROJECT_NAME" variable to Adding_two_integers_prj
    project(Adding_two_integers_prj)

    # Create project "CoreMQTT unit test", that must be built with C language
    #   - C and CXX (C++) are default languages if no language is provided
    #   - with version we can have several same projects, but different version
    project("CoreMQTT unit test" VERSION 1.0.0 LANGUAGES C)
)
set_target_properties( # https://cmake.org/cmake/help/latest/command/set_target_properties.html
    
    # Set property on target "Example" that its linker language will be CXX (C++)
    set_target_properties(Example PROPERTIES LINKER_LANGUAGE CXX)
)
target_compile_definitions( # https://cmake.org/cmake/help/latest/command/target_compile_definitions.html

    # Add MQTT_DO_NOT_USE_CUSTOM_CONFIG=1 preprocessor variable (MACRO) into "coverity_analysis" target
    target_compile_definitions(coverity_analysis PUBLIC MQTT_DO_NOT_USE_CUSTOM_CONFIG=1 )
)
#----------------------------------------------------------------------------------------------------------#
target_include_directories( # https://cmake.org/cmake/help/latest/command/target_include_directories.html
    
    # Include files from IO directory into "Adding_two_integers.exe" target
    target_include_directories(Adding_two_integers PUBLIC IO)
)
#----------------------------------------------------------------------------------------------------------#
target_link_directories( # https://cmake.org/cmake/help/latest/command/target_link_directories.html
    
    # Add directories in which target whould look when linking libraries
    target_link_directories(Multiple_classes_and_friend
        PUBLIC out/build/Point3d 
        PUBLIC out/build/Vector3d
    )
)
#----------------------------------------------------------------------------------------------------------#
target_link_libraries( # https://cmake.org/cmake/help/latest/command/target_link_libraries.html

    # Link "Point3d" and "Vector3d" libraries with "Multiple_classes_and_friend" target
    # - Point3d and Vector3d are names of the target created with add_library()
    target_link_libraries(Multiple_classes_and_friend Point3d Vector3d)
)
#----------------------------------------------------------------------------------------------------------#
target_sources( # https://cmake.org/cmake/help/latest/command/target_sources.html

    # Link source file "Point3d.cpp" into Multiple_classes_and_friend target
    target_sources(Multiple_classes_and_friend PUBLIC Point3d.cpp)
)