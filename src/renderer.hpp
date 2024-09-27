#pragma once

#include "mesh.hpp"


class Renderer
{
public:
    Renderer();
    ~Renderer() = default;

    void render();

private:
    Mesh m_mesh = {};

};