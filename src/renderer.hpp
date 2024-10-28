#pragma once

#include <memory>
#include "mesh.hpp"
#include "voxel.hpp"
#include "constants.hpp"
#include "meshDataHandler.hpp"



class Renderer
{
public:
    Renderer();
    ~Renderer() = default;

    void render();

private:
    std::unique_ptr<MeshDataHandler> m_meshDataHandler = nullptr;
    Mesh m_meshVoxel = {};
    Mesh m_meshTriangle = {};
    int m_currentResolution = -1;
};