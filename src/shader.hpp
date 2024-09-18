#pragma once

#include <iostream>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <fstream>
#include <sstream>

class Shader
{
public:
    Shader( const char *shaderPath, bool isVertexShader, unsigned int tecID );
    unsigned int getID();

private:
    unsigned m_ID;
    void checkCompileErrors( unsigned int shader );
};
