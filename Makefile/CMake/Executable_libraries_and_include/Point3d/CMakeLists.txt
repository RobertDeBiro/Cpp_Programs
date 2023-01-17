add_library(Point3d Point3d.cpp)

target_include_directories(Point3d
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/Vector3d
)