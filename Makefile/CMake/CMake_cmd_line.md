# CMake command-line tool

- CMake reference: <https://cmake.org/cmake/help/latest/manual/cmake.1.html>

---

## Generate a Project Buildsystem on Linux

```bash
cmake -S <path-to-source> -B <path-to-build>
cmake -S . -B out/build
```

---

## Generate a Project Buildsystem on Windows

```bash
cmake -S <path-to-source> -B <path-to-build> -G <build-system-generator>
cmake -S . -B out/build -G "MSYS Makefiles"
```

- when working in Windows and using MSYS2/MinGW64 for building the code (Linux tools such as gcc, gdb),
   we need to use "MSYS Makefiles" CMake build system generator
- there are various CMake build system generators:  
  <https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html#manual:cmake-generators(7)>

---

## Create or update a CMake CACHE entry by changing already defined variable

```bash
cmake -D<variable>=<value> -S . -B out/build
cmake -DGLFW_BUILD_DOCS=OFF -S . -B out/build
```

---

## Run CMake together with defining preprocessor variable (MACRO)

```bash
cmake -DCMAKE_CXX_FLAGS=" -DRANDOM_MACRO_VAL=1000 " -DCMAKE_CXX_FLAGS=" -DRANDOM_MACRO " -S . -B out/build
```

- did't work for some reason!
