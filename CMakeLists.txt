set(NAME "TestVoxelizer")

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
        src/renderer.hpp)

find_package(SDL2 REQUIRED)
target_include_directories(${NAME} PRIVATE ${SDL2_INCLUDE_DIRS})
target_link_libraries(${NAME} PRIVATE ${SDL2_LIBRARIES})

find_package(GLEW REQUIRED)
target_include_directories(${NAME} PRIVATE ${GLEW_INCLUDE_DIRS})
target_link_libraries(${NAME} PRIVATE GLEW::GLEW)

find_package(GLM REQUIRED)
target_include_directories(${NAME} PRIVATE ${GLM_INCLUDE_DIRS})
target_link_libraries(${NAME} PRIVATE glm::glm)