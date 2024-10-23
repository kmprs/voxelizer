#include "openGLHandler.hpp"
#include "shader.hpp"

unsigned int programID;

OpenGLHandler::OpenGLHandler()
        :
        m_shaderHandler( std::make_shared<ShaderHandler>())
{
    if ( GLEW_OK != glewInit())
    {
        std::cout << "Failed to Init GLEW" << std::endl;
    }
    programID = glCreateProgram();

    // set scene OpenGL
    glEnable( GL_DEPTH_TEST );
    glEnable( GL_CULL_FACE );
//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // shaders setup
    Shader vertexShader = {"../src/shaders/shader.vs.vert", true, m_shaderHandler->getID()};
    Shader fragmentShader = {"../src/shaders/shader.fs.frag", false, m_shaderHandler->getID()};
    m_shaderHandler->add( vertexShader );
    m_shaderHandler->add( fragmentShader );
    m_shaderHandler->link();
}

void OpenGLHandler::use() const
{
    glUseProgram( programID );
}

std::shared_ptr<ShaderHandler> OpenGLHandler::getShaderHandler()
{
    return m_shaderHandler;
}
