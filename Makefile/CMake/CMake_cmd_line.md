CMake command-line tool
==========================================================================
CMake reference: https://cmake.org/cmake/help/latest/manual/cmake.1.html

--------------------------------------------------------------------------
**Generate a Project Buildsystem on Linux:**

    cmake -S <path-to-source> -B <path-to-build>
    cmake -S . -B out/build

--------------------------------------------------------------------------
**Generate a Project Buildsystem on Windows**

    cmake -S <path-to-source> -B <path-to-build> -G <build-system-generator>
    cmake -S . -B out/build -G "MinGW Makefiles

 - when working in Windows and using MinGW for building the code (Linux tools such as gcc, gdb), 
   we need to use "MinGW Makefiles" CMake build system generator:  
   https://cmake.org/cmake/help/latest/generator/MinGW%20Makefiles.html
 - there are various CMake build system generators:  
   https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html#manual:cmake-generators(7):

--------------------------------------------------------------------------
**Create or update a CMake CACHE entry by changing already defined variable:**

    cmake -D<variable>=<value> -S . -B out/build
    cmake -DGLFW_BUILD_DOCS=OFF -S . -B out/build


--------------------------------------------------------------------------
**Run CMake together with defining preprocessor variable (MACRO)**

    cmake -DCMAKE_CXX_FLAGS=" -DRANDOM_MACRO_VAL=1000 " -DCMAKE_CXX_FLAGS=" -DRANDOM_MACRO " -S . -B out/build

  - doesn't work for some reason!