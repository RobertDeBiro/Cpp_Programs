#!/bin/bash

##### Windows version #####
# cmake -S ../ -B ../out/build -G "MSYS Makefiles"

##### Linux version #####
cmake -DCMAKE_BUILD_TYPE=Release -S ../ -B ../out/build