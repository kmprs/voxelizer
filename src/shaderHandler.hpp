#pragma once

#include "shader.hpp"
#include <iostream>
#include <vector>


class ShaderHandler
{
public: 
    ShaderHandler();
    ~ShaderHandler() = default;
    void link();
    void use() const;
    void add(const Shader &shader);
    std::vector<Shader> getShaders();
    void setMat4( const std::string &name, const glm::mat4 &mat ) const;
    [[nodiscard]] unsigned int getID() const;
    void uploadInt( const std::string &name, int value ) const;

private:
    std::vector<Shader> m_shaders;
    static void checkCompileErrors( unsigned int shader, const std::string &type );
    static GLint getVariableLocation( const char *name );
};
