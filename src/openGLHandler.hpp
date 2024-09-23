#pragma once

#include "shaderHandler.hpp"


class OpenGLHandler
{
public:
    OpenGLHandler();
    ~OpenGLHandler() = default;
    void use() const;
    std::shared_ptr<ShaderHandler> getShaderHandler();

private:
    std::shared_ptr<ShaderHandler> m_shaderHandler = nullptr;
};