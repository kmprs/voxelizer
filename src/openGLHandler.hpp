#pragma once

#include "shaderHandler.hpp"
#include "dataHandler.hpp"

class OpenGLHandler
{
public:
    OpenGLHandler();
    ~OpenGLHandler() = default;
    static void use() ;
    std::shared_ptr<ShaderHandler> getShaderHandler();

private:
    std::shared_ptr<ShaderHandler> m_shaderHandler = nullptr;
};