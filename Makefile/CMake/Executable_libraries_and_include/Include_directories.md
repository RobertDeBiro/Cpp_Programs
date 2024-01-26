# Configure our build to properly *include* files

- `target_include_directories()` is needed in subdirectories only if we use several libraries in addition to executable
  - those examples are shown in this file
- if we use only `add_executable()`, and optionally `target_sources()`, it is sufficient to have only one `target_include_directories()` in source directory

---

## 1) Include directories for executable and libraries, in particular

- use `target_include_directories()` command for executable and libraries, in particular

### 1a) CMakeLists.txt - main

```bash
target_include_directories(Multiple_classes_and_friend
    PUBLIC
        Point3d
        Vector3d
)

target_link_libraries(Multiple_classes_and_friend Point3d Vector3d)
```

### 1b) CmakeLists.txt - Point3d

```bash
add_library(Point3d Point3d.cpp)

target_include_directories(Point3d
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/Vector3d
)
```

### 1c) CmakeLists.txt - Vector3d

```bash
add_library(Vector3d Vector3d.cpp)

target_include_directories(Vector3d
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/Point3d
)
```

---

## 2) Include directories only for libraries

- use `target_include_directories()`` command for libraries, and then link executable with those libraries
- since `main` doesn't includes directories directly, it must include them via libraries, by linking with them, hence
  libraries must include directories PUBLICly

### 2a) CMakeLists.txt - main

```bash
target_link_libraries(Multiple_classes_and_friend Point3d Vector3d)
```

### 2b) CmakeLists.txt - Point3d

```bash
add_library(Point3d Point3d.cpp)

target_include_directories(Point3d
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/Vector3d
)
```

### 2c) CmakeLists.txt - Vector3d

```bash
add_library(Vector3d Vector3d.cpp)

target_include_directories(Vector3d
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/Point3d
)
```

---

## 3) Include directories for every target in current directory and all child directories

### 3a) CMakeLists.txt - main

```bash
include_directories(Point3d Vector3d)
target_link_libraries(Multiple_classes_and_friend Point3d Vector3d)
```

### 3b) CmakeLists.txt - Point3d

```bash
add_library(Point3d Point3d.cpp)
```

### 3c) CmakeLists.txt - Vector3d

```bash
add_library(Vector3d Vector3d.cpp)
```
