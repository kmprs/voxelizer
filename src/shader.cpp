#include "shader.hpp"

Shader::Shader( const char* shaderPath, bool isVertexShader, unsigned int tecID )
{
    std::string sCode;
    std::ifstream shaderFile;
    shaderFile.exceptions( std::ifstream::failbit | std::ifstream::badbit );

    try
    {
        shaderFile.open( shaderPath );
        std::stringstream shaderStream;
        shaderStream << shaderFile.rdbuf();
        shaderFile.close();
        sCode = shaderStream.str();
    }
    catch ( std::ifstream::failure &e )
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
    }
    const char* shaderCode = sCode.c_str();
    m_ID = glCreateShader( isVertexShader ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER );
    glShaderSource( m_ID, 1, &shaderCode, nullptr );
    glCompileShader( m_ID );
    checkCompileErrors( m_ID );
    glAttachShader( tecID, m_ID );
}

unsigned int Shader::getID()
{
    return m_ID;
}

void Shader::checkCompileErrors( unsigned int shader )
{
    int success;
    char infoLog[1024];
    glGetShaderiv( shader, GL_COMPILE_STATUS, &success );
    if ( !success )
    {
        glGetShaderInfoLog( shader, 1024, nullptr, infoLog );
        std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << "SHADER" << "\n" << infoLog
                  << "\n -- --------------------------------------------------- -- " << std::endl;
    }
}