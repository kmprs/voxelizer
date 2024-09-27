#pragma once

#include "shader.hpp"
#include <vector>
#include <glm/gtc/type_ptr.hpp>


class ShaderHandler
{
public: 
    ShaderHandler();
    ~ShaderHandler() = default;
    void link();
    void add(const Shader &shader);
    [[nodiscard]] unsigned int getID() const;
    void setMat4( const std::string &name, const glm::mat4 &mat ) const;
    void setVec3( const std::string &name, const glm::vec3 &vec ) const;
    void setFloat(const std::string &name, float value) const;

private:
    std::vector<Shader> m_shaders;
    static void checkCompileErrors( unsigned int shader, const std::string &type );
    static GLint getVariableLocation( const char *name );
};
