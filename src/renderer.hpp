#pragma once

#include <memory>
#include "mesh.hpp"
#include "voxel.hpp"
#include "constants.hpp"


class Renderer
{
public:
    Renderer();
    ~Renderer() = default;

    void render();

private:
    Mesh m_meshVoxel = {};
    Mesh m_meshTriangle = {};
};