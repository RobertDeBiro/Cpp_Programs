##################################################
# add_executable
##################################################

set(EXEC Adding_two_integers)

# Build one src file
function(add_exec_src_file)

    add_executable(${EXEC} main.cpp IO/io.cpp)

endfunction()

# Build multiple src files from directory
function(add_exec_src_dir)

    aux_source_directory(./IO SRC)
    add_executable(${EXEC} main.cpp ${SRC})

endfunction()