#!/bin/bash

##### Windows version #####
# cmake -DGLFW_BUILD_DOCS=OFF -S . -B ../out/build -G "MSYS Makefiles"

##### Linux version #####
cmake -DGLFW_BUILD_DOCS=OFF -S . -B ../out/build
