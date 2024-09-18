#include "openGLHandler.hpp"
#include "shader.hpp"

OpenGLHandler::OpenGLHandler()
        :
        m_shaderHandler( std::make_unique<ShaderHandler>())
{
    // set up OpenGL
    glEnable( GL_DEPTH_TEST );

    // shaders setup
    Shader vertexShader = {"../src/shaders/shader.vs.vert", true, m_shaderHandler->getID()};
    Shader fragmentShader = {"../src/shaders/shader.fs.frag", false, m_shaderHandler->getID()};
    m_shaderHandler->add(vertexShader);
    m_shaderHandler->add(fragmentShader);
    m_shaderHandler->link();
}
