add_library(Vector3d Vector3d.cpp)

target_include_directories(Vector3d
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/Point3d
)