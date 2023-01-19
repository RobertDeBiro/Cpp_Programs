# cmake-commands: https://cmake.org/cmake/help/latest/manual/cmake-commands.7.html

cmake_minimum_required( # https://cmake.org/cmake/help/latest/command/cmake_minimum_required.html
    
    # Minimum version of cmake that must run on a machine in order to 
    # execute current CMakeLists.txt is version 3.24.1
    cmake_minimum_required(VERSION 3.24.1)

    # - cmake version can be checked by executing "cmake --version" inside the terminal
)
#----------------------------------------------------------------------------------------------------------#
execute_process( # https://cmake.org/cmake/help/latest/command/execute_process.html
    
    # Open readme.md file in notepad++, and in addition:
    #  - save result of the last child process into variable README_ID
    execute_process(
        COMMAND notepad++ readme.md
        RESULT_VARIABLE README_ID
    )

    # Execute command bash -c <STRING>
    execute_process(
        COMMAND bash -c "ls ${TEST_SRC_DIR}/inc/mqtt_connection_manager"
    )
)
#----------------------------------------------------------------------------------------------------------#
foreach( # https://cmake.org/cmake/help/latest/manual/cmake-commands.7.html

    set(A 0;1)
    set(B 2 3)
    set(C "4 5")
    set(D 6;7 8)
    set(E "")
    foreach(X IN LISTS A B C D E)
        message(STATUS "X=${X}")
    endforeach()

    # Outcome:
    # -- X=0
    # -- X=1
    # -- X=2
    # -- X=3
    # -- X=4 5
    # -- X=6
    # -- X=7
    # -- X=8
)
endforeach( # https://cmake.org/cmake/help/latest/command/endforeach.html
)
#----------------------------------------------------------------------------------------------------------#
function( # https://cmake.org/cmake/help/latest/command/function.html
    
    # Create a function called "open_notepad"
    function(open_notepad)
        execute_process(
            COMMAND notepad++ readme.md
            RESULT_VARIABLE README_ID
        )
    endfunction()

    # Call the function
    open_notepad()
)
endfunction( # https://cmake.org/cmake/help/latest/command/endfunction.html
)
#----------------------------------------------------------------------------------------------------------#
get_filename_component( # https://cmake.org/cmake/help/latest/command/get_filename_component.html

    set(FILE_VAR /c/Users/rar/Desktop/Posao/Programs/VSCode/Cpp/Makefile_practice/CMake/Miscellaneous/filename.txt)
    
    # Save directory in which the file from FILE_VAR is present, into variable VAR
    get_filename_component(VAR ${FILE_VAR} DIRECTORY)
    # Save only the file name of the file from FILE_VAR, into variable VAR
    get_filename_component(VAR ${FILE_VAR} NAME)


    set(FILE_VAR filename.txt)
    
    # Save full path to the file from FILE_VAR, into variable VAR
    get_filename_component(VAR ${FILE_VAR} ABSOLUTE)

    # Save full path to the file from FILE_VAR with symlinks resolved, into variable VAR
    get_filename_component(VAR ${FILE_VAR} REALPATH)
)
#----------------------------------------------------------------------------------------------------------#
include( # https://cmake.org/cmake/help/latest/command/include.html
    
    # Include cmake-module "CMakePrintHelpers"
    include(CMakePrintHelpers)

    # Include custom-module "Custom_funct_module"
    include(Custom_funct_module)
)
#----------------------------------------------------------------------------------------------------------#
list ( # https://cmake.org/cmake/help/latest/command/list.html

    # Append element /home/.../coreMQTT to the CMAKE_MODULE_PATH list
    list(
        APPEND
        CMAKE_MODULE_PATH
            /home/dev/FreeRTOS/FreeRTOS-Plus/Source/Application-Protocols/coreMQTT
    )

    # Get element from the list "MQTT_INCLUDE_PUBLIC_DIRS" and place it into variable "MQTT_INCLUDE"
    # - list cannot be retrieved from ${...}
    # - following wouldn't work: list(GET ${MQTT_INCLUDE_PUBLIC_DIRS} 0 MQTT_INCLUDE)
    list(GET MQTT_INCLUDE_PUBLIC_DIRS 0 MQTT_INCLUDE)
)
#----------------------------------------------------------------------------------------------------------#
message( # https://cmake.org/cmake/help/latest/command/message.html
    
    # Print status message, with README_ID value
    message(STATUS ${CMAKE_MODULE_PATH})

    # Print status message, with README_ID value and a text
    message(STATUS "CMAKE_MODULE_PATH = ${CMAKE_MODULE_PATH}")

    # Print status message with a text
    message(STATUS "*** CMakeLists.txt executed! ***")
)
#----------------------------------------------------------------------------------------------------------#
set( # https://cmake.org/cmake/help/latest/command/set.html
    
    # Set "CMAKE_MODULE_PATH" variable to "custom_modules" value
    set(CMAKE_MODULE_PATH custom_modules)
)
#----------------------------------------------------------------------------------------------------------#