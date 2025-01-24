########## Create gresource from resource files ##########

## Find a program called 'glib-compile-resources' and save it to 'GLIB_COMPILE_RESOURCES' variable
find_program(GLIB_COMPILE_RESOURCES NAMES glib-compile-resources REQUIRED)

## Generate a list of files that match globbing expression 'assets/*' (save every file from 'assets' dir)
## and store those files inside 'RESOURCE_SOURCES'
file(GLOB_RECURSE RESOURCE_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/assets/*)

set(GRESOURCE_C com.ronna-medical.rtkplanning.resource.c)
set(GRESOURCE_XML assets/resource.xml)

########## Add a custom build rule to the generated build system ##########
add_custom_command(
        OUTPUT ${GRESOURCE_C} ## Define that the command should produce output files written inside 'GRESOURCE_C' var
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/assets ## Command will be run inside 'assets' directory
        COMMAND ${GLIB_COMPILE_RESOURCES} ## Commands that will be executed at build time are present inside 'GLIB_COMPILE_RESOURCES' var
        ARGS ## Arguments of the 'glib-compile-resources' command (in this example: '--internal', '--generate-source' and '--target')
        --internal ## It informs the tool that the generated C source file will be compiled into a program or library and is not intended to be separately compiled or installed.
        --generate-source ## flag that instructs the 'glib-compile-resources' to generate C source code along with the binary resource file
        --target=${CMAKE_CURRENT_BINARY_DIR}/${GRESOURCE_C} ## the name of the output C source file
        ${CMAKE_CURRENT_SOURCE_DIR}/${GRESOURCE_XML} ## XML resource file used by 'glib-compile-resources' command
        VERBATIM ## prohibit CMake to interpret escape sequences or to replace variables in the command arguments
        MAIN_DEPENDENCY ${CMAKE_CURRENT_SOURCE_DIR}/${GRESOURCE_XML} ## Define that custom command will be re-run in following builds if file written in 'GRESOURCE_XML' was changed
        DEPENDS ${RESOURCE_SOURCES} ## Define that custom command will be re-run in following builds if files written in 'RESOURCE_SOURCES' were changed
)

## Create meta-target called 'project_resources'
##  - since it doesn't have COMMAND argument set, it means that it is meta-target i.e. that target won't produce any output files
##    or execute any specific actions during the build process
##  - this is useful for organizing our build system, especially when we have multiple targets and want to define their relationships
##  - by setting DEPENDS, we define that if we run 'make project_resources', 'GRESOURCE_C' needs to be built first
add_custom_target(project_resources DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/${GRESOURCE_C})


## Generate a list of files that match globbing expression '.cpp' and '.h' and store those files inside 'SOURCE'
##  - including header files in this list is somewhat redundant since headers are not compiled directly, they are included in source files
##  - on the other side, listing header files in the 'add_executable' command or the 'GLOB_RECURSE' function is typically done for convenience in IDEs - 
##    this way, the IDE can see all project files, including headers, which is useful for navigation and code browsing
file(GLOB_RECURSE SOURCE *.cpp *.h)

## Create executable called 'rtkplanning' from files from 'SOURCE' and 'GRESOURCE_C'
add_executable(rtkplanning
    ${SOURCE}
    ${CMAKE_CURRENT_BINARY_DIR}/${GRESOURCE_C}
)

## Set that we will use C++20 standard ('cxx_std_20') when compiling 'rtkplanning'
target_compile_features(rtkplanning PUBLIC cxx_std_20)

# Set resources as project dependency
set_source_files_properties(${CMAKE_CURRENT_BINARY_DIR}/${GRESOURCE_C} PROPERTIES GENERATED TRUE)
add_dependencies(rtkplanning project_resources)

target_link_libraries(rtkplanning ${GTK4_LIBRARIES})
target_link_libraries(rtkplanning ${ADWAITA_LIBRARIES})
target_link_libraries(rtkplanning ${VTK_LIBRARIES})
vtk_module_autoinit(TARGETS rtkplanning MODULES ${VTK_LIBRARIES})
target_link_libraries(rtkplanning ${ITK_LIBRARIES})
target_link_libraries(rtkplanning ${DCMTK_LIBRARIES})
target_link_libraries(rtkplanning ${SQLite3_LIBRARIES})
target_link_libraries(rtkplanning ${OpenCV_LIBS} opencv_core opencv_video opencv_imgproc)
target_link_libraries(rtkplanning Eigen3::Eigen)
target_link_libraries(rtkplanning rtkcommon)
target_link_libraries(rtkplanning rtkcommunication)

target_include_directories(rtkplanning PUBLIC ${RTKCOMMON_INCLUDE})

target_include_directories(rtkplanning PUBLIC ${CMAKE_CURRENT_LIST_DIR})
target_include_directories(rtkplanning PUBLIC ${CMAKE_CURRENT_LIST_DIR}/database)
target_include_directories(rtkplanning PUBLIC ${CMAKE_CURRENT_LIST_DIR}/database/model)
target_include_directories(rtkplanning PUBLIC ${CMAKE_CURRENT_LIST_DIR}/helpers)
target_include_directories(rtkplanning PUBLIC ${CMAKE_CURRENT_LIST_DIR}/ui)
target_include_directories(rtkplanning PUBLIC ${CMAKE_CURRENT_LIST_DIR}/ui/main)
target_include_directories(rtkplanning PUBLIC ${CMAKE_CURRENT_LIST_DIR}/ui/main/database)
target_include_directories(rtkplanning PUBLIC ${CMAKE_CURRENT_LIST_DIR}/ui/main/media)
target_include_directories(rtkplanning PUBLIC ${CMAKE_CURRENT_LIST_DIR}/ui/main/pacs/query)
target_include_directories(rtkplanning PUBLIC ${CMAKE_CURRENT_LIST_DIR}/ui/main/pacs/settings)
target_include_directories(rtkplanning PUBLIC ${CMAKE_CURRENT_LIST_DIR}/ui/plan)
target_include_directories(rtkplanning PUBLIC ${CMAKE_CURRENT_LIST_DIR}/ui/plan/markers)
target_include_directories(rtkplanning PUBLIC ${CMAKE_CURRENT_LIST_DIR}/ui/plan/trajectories)
target_include_directories(rtkplanning PUBLIC ${CMAKE_CURRENT_LIST_DIR}/ui/plan/sync)

target_include_directories(rtkplanning PRIVATE ${CMAKE_SOURCE_DIR}/external)
