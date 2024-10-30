#include "shaderHandler.hpp"

extern unsigned int programID;

ShaderHandler::ShaderHandler()
{
}

void ShaderHandler::link()
{
    glLinkProgram( programID );
    checkCompileErrors( programID, "PROGRAM" );
    for ( Shader s: m_shaders )
    {
        glDeleteShader( s.getID() );
    }
}

void ShaderHandler::add( const Shader &shader )
{
    m_shaders.emplace_back(shader);
}

unsigned int ShaderHandler::getID() const
{
    return programID;
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
    GLint loc = glGetUniformLocation( programID, name );
    if ( loc == -1 )
    {
        std::cerr << "Uniform: " << name << " not found" << std::endl;
        throw;
    }
    return loc;

}

void ShaderHandler::setMat4( const std::string &name, const glm::mat4 &mat ) const
{
    glUseProgram(programID);
    GLint location = glGetUniformLocation(programID, name.c_str());
    glUniformMatrix4fv( location, 1, GL_FALSE, &mat[0][0] );
}

void ShaderHandler::setVec3( const std::string &name, const glm::vec3 &vec ) const
{
    glUseProgram(programID);
    GLint location = glGetUniformLocation( programID, name.c_str());
    glUniform3fv(location, 1, &vec[0]);
}

void ShaderHandler::setFloat( const std::string &name, float value ) const
{
    glUseProgram(programID);
    GLint location = glGetUniformLocation( programID, name.c_str());
    glUniform1f(location, value);
}

void ShaderHandler::setInt( const std::string &name, int value ) const
{
    glUseProgram(programID);
    GLint location = glGetUniformLocation( programID, name.c_str());
    glUniform1i(location, value);
}