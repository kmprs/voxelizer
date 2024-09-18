#include "shaderHandler.hpp"

unsigned int shaderHandlerID;

void ShaderHandler::link()
{
    glLinkProgram( shaderHandlerID );
    checkCompileErrors( shaderHandlerID, "PROGRAM" );
    for ( Shader s: m_shaders )
    {
        glDeleteShader( s.getID() );
    }
}

void ShaderHandler::use() const
{
    glUseProgram( shaderHandlerID );
}

void ShaderHandler::add( const Shader &shader )
{
    m_shaders.emplace_back(shader);
}

std::vector<Shader> ShaderHandler::getShaders()
{
    return m_shaders;
}

void ShaderHandler::setMat4( const std::string &name, const glm::mat4 &mat ) const
{
    glUniformMatrix4fv( glGetUniformLocation( shaderHandlerID, name.c_str()), 1, GL_FALSE, &mat[0][0] );
}

unsigned int ShaderHandler::getID() const
{
    return shaderHandlerID;
}

void ShaderHandler::uploadInt( const std::string &name, const int value ) const
{
    int location = getVariableLocation( name.c_str() );
    glUniform1i( location, value );
}

void ShaderHandler::checkCompileErrors( unsigned int shader, const std::string &type )
{
    int success;
    char infoLog[1024];
    glGetProgramiv( shader, GL_LINK_STATUS, &success );
    if ( !success )
    {
        glGetProgramInfoLog( shader, 1024, nullptr, infoLog );
        std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog
                  << "\n -- --------------------------------------------------- -- " << std::endl;
    }
}

GLint ShaderHandler::getVariableLocation( const char* name )
{
    GLint loc = glGetUniformLocation( shaderHandlerID, name );
    if ( loc == -1 )
    {
        std::cerr << "Uniform: " << name << " not found" << std::endl;
        throw;
    }
    return loc;

}


