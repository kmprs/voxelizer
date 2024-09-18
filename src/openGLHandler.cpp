#include "openGLHandler.hpp"
#include "shader.hpp"

unsigned int programID;

OpenGLHandler::OpenGLHandler()
        :
        m_shaderHandler( std::make_unique<ShaderHandler>())
{
    if ( GLEW_OK != glewInit())
    {
        std::cout << "Failed to Init GLEW" << std::endl;
    }
    programID = glCreateProgram();

    // set up OpenGL
    glEnable( GL_DEPTH_TEST );

    // shaders setup
    Shader vertexShader = {"../src/shaders/shader.vs.vert", true, m_shaderHandler->getID()};
    Shader fragmentShader = {"../src/shaders/shader.fs.frag", false, m_shaderHandler->getID()};
    m_shaderHandler->add(vertexShader);
    m_shaderHandler->add(fragmentShader);
    m_shaderHandler->link();
}
