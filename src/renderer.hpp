#pragma once

#include <memory>
#include "mesh.hpp"
#include "voxel.hpp"
#include "triangleFace.hpp"
#include "constants.hpp"


class Renderer
{
public:
    Renderer();
    ~Renderer() = default;

    void render();

private:
    Mesh m_mesh = { std::vector<std::shared_ptr<Renderable>>() };
    std::vector<std::shared_ptr<Renderable>> m_renderables = {};
};