# Create our executable, made of several source files

---
## 1) Create executable for every source file

**CMakeLists.txt - main**

    add_executable(Multiple_classes_and_friend  
        main.cpp  
        Point3d/Point3d.cpp  
        Vector3d/Vector3d.cpp
    ) 

---
## 2) Create executable and add sources
### 2.1) From one *CMakeLists.txt* file

**CMakeLists.txt - main**

    add_executable(Multiple_classes_and_friend main.cpp)
    target_sources(Multiple_classes_and_friend
        PUBLIC
            Point3d/Point3d.cpp
            Vector3d/Vector3d.cpp
    )

### 2.2) From several *CMakeLists.txt* files
- create executable from only *main.cpp* file and later on link other sources
that where created as libraries inisde their *CMakeLists.txt*

**CMakeLists.txt - main**

    add_executable(Multiple_classes_and_friend main.cpp)

    add_subdirectory(Point3d)
    add_subdirectory(Vector3d)

**CmakeLists.txt - Point3d**

    target_sources(Multiple_classes_and_friend PUBLIC Point3d.cpp)

**CmakeLists.txt - Vector3d**

    target_sources(Multiple_classes_and_friend PUBLIC Vector3d.cpp)

---
## 3) Create executable and add libraries:
- create executable from only *main.cpp* file and later on link other sources
that where created as libraries inisde their *CMakeLists.txt*

**CMakeLists.txt - main**

    add_executable(Multiple_classes_and_friend main.cpp)
    target_link_libraries(Multiple_classes_and_friend Point3d Vector3d)
    
**CmakeLists.txt - Point3d**

    add_library(Point3d Point3d.cpp)
    
**CmakeLists.txt - Vector3d**

    add_library(Vector3d Vector3d.cpp)