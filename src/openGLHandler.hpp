#pragma once

#include "shaderHandler.hpp"


class OpenGLHandler
{
public:
    OpenGLHandler();
    ~OpenGLHandler() = default;
    void use() const;

private:
    std::unique_ptr<ShaderHandler> m_shaderHandler = nullptr;
};