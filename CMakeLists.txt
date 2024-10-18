set(NAME "Voxelizer")

cmake_minimum_required(VERSION 3.26)
project(${NAME})

set(CMAKE_CXX_STANDARD 17)

add_executable(${NAME} main.cpp
        src/program.cpp
        src/program.hpp
        src/windowHandler.cpp
        src/windowHandler.hpp
        src/eventHandler.cpp
        src/eventHandler.hpp
        src/openGLHandler.cpp
        src/openGLHandler.hpp
        src/shader.cpp
        src/shader.hpp
        src/shaderHandler.cpp
        src/shaderHandler.hpp
        src/renderer.cpp
        src/renderer.hpp
        src/camera.cpp
        src/camera.hpp
        src/constants.hpp
        src/transformator.cpp
        src/transformator.hpp
        src/sceneHandler.cpp
        src/sceneHandler.hpp
        src/mesh.cpp
        src/mesh.hpp
        src/types.hpp
        src/renderable.hpp
        src/voxel.cpp
        src/voxel.hpp
        src/triangleFace.cpp
        src/triangleFace.hpp
        src/dataHandler.cpp
        src/dataHandler.hpp
        src/parser.hpp
        src/objParser.cpp
        src/objParser.hpp
        src/util.cpp
        src/util.hpp
        src/octreeNode.cpp
        src/octreeNode.hpp
        src/octreeVoxelizer.cpp
        src/octreeVoxelizer.hpp
        src/bvhNode.cpp
        src/bvhNode.hpp
        src/voxelizer.hpp
        src/bresenhamVoxelizer.cpp
        src/bresenhamVoxelizer.hpp)

find_package(SDL2 REQUIRED)
target_include_directories(${NAME} PRIVATE ${SDL2_INCLUDE_DIRS})
target_link_libraries(${NAME} PRIVATE ${SDL2_LIBRARIES})

find_package(GLEW REQUIRED)
target_include_directories(${NAME} PRIVATE ${GLEW_INCLUDE_DIRS})
target_link_libraries(${NAME} PRIVATE GLEW::GLEW)

find_package(GLM REQUIRED)
target_include_directories(${NAME} PRIVATE ${GLM_INCLUDE_DIRS})
target_link_libraries(${NAME} PRIVATE glm::glm)