cmake_minimum_required(VERSION 3.16)
project(3D_engine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(SDL3 REQUIRED)

add_executable(3D_engine)

target_sources(3D_engine
    PRIVATE
        src/main.cpp
        src/renderer/core/face.cpp
        src/renderer/core/mesh.cpp
        src/renderer/render/renderer.cpp
        src/renderer/camera/camera.cpp
        src/renderer/loaders/obj_loader.cpp
)

target_include_directories(3D_engine
    PRIVATE
        ${SDL3_INCLUDE_DIRS}
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(3D_engine PRIVATE ${SDL3_LIBRARIES})
