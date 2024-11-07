set(NAME "Voxelizer")

cmake_minimum_required(VERSION 3.26)
project(${NAME})

set(CMAKE_CXX_STANDARD 17)

add_executable(${NAME} main.cpp
        src/program.cpp
        src/program.hpp
        src/windows/windowHandler.cpp
        src/windows/windowHandler.hpp
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
        src/meshDataHandler.cpp
        src/meshDataHandler.hpp
        src/parser.hpp
        src/objParser.cpp
        src/objParser.hpp
        src/util.cpp
        src/util.hpp
        src/octreeNode.cpp
        src/octreeNode.hpp
        src/octreeBVHVoxelizer.cpp
        src/octreeBVHVoxelizer.hpp
        src/bvhNode.cpp
        src/bvhNode.hpp
        src/voxelizer.hpp
        src/bresenhamVoxelizer.cpp
        src/bresenhamVoxelizer.hpp
        src/gui/gui.cpp
        src/gui/gui.hpp
        src/dataHandler.cpp
        src/dataHandler.hpp
        src/naiveVoxelizer.cpp
        src/naiveVoxelizer.hpp
        src/octreeVoxelizer.cpp
        src/octreeVoxelizer.hpp
        src/bvhVoxelizer.cpp
        src/bvhVoxelizer.hpp

        dependencies/imgui/imconfig.h
        dependencies/imgui/imgui.cpp
        dependencies/imgui/imgui.h
        dependencies/imgui/imgui_demo.cpp
        dependencies/imgui/imgui_draw.cpp
        dependencies/imgui/imgui_tables.cpp
        dependencies/imgui/imgui_widgets.cpp
        dependencies/imgui/imgui_impl_opengl3.cpp
        dependencies/imgui/imgui_impl_opengl3.h
        dependencies/imgui/imgui_impl_opengl3_loader.h
        dependencies/imgui/imgui_impl_sdl2.cpp
        dependencies/imgui/imgui_impl_sdl2.h
        dependencies/file_dialog/ImGuiFileDialog.cpp
        dependencies/file_dialog/ImGuiFileDialog.h
        dependencies/file_dialog/ImGuiFileDialogConfig.h
        src/windows/renderingWindowHandler.cpp
        src/windows/renderingWindowHandler.hpp
        src/gui/mainGui.cpp
        src/gui/mainGui.hpp
        src/windows/benchmarkWindowHandler.cpp
        src/windows/benchmarkWindowHandler.hpp
        src/gui/benchmarkGui.cpp
        src/gui/benchmarkGui.hpp
)


find_package(SDL2 REQUIRED)
target_include_directories(${NAME} PRIVATE ${SDL2_INCLUDE_DIRS})
target_link_libraries(${NAME} PRIVATE ${SDL2_LIBRARIES})

find_package(GLEW REQUIRED)
target_include_directories(${NAME} PRIVATE ${GLEW_INCLUDE_DIRS})
target_link_libraries(${NAME} PRIVATE GLEW::GLEW)

find_package(GLM REQUIRED)
target_include_directories(${NAME} PRIVATE ${GLM_INCLUDE_DIRS})
target_link_libraries(${NAME} PRIVATE glm::glm)