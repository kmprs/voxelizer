#pragma once

#include "shaderHandler.hpp"


class OpenGLHandler
{
public:
    OpenGLHandler();
    ~OpenGLHandler() = default;

private:
    std::unique_ptr<ShaderHandler> m_shaderHandler = nullptr;

    float m_vertices[9] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f,  0.5f, 0.0f
    };
};