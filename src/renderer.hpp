#pragma once

#include <iostream>
#include <vector>
#include "GL/glew.h"


class Renderer
{
public:
    Renderer();
    ~Renderer() = default;

    void render();

private:
    // MESH CLASS METHODS AND ATTRIBUTES
    GLuint m_VAO = 0;
    GLuint m_VBO = 0;
    GLuint m_EBO = 0;
    std::vector<float> m_vertices = {
              0, .5f, 0,
             .5f, -.5f,  0,
            -.5f, -.5f,  0
    };
    std::vector<unsigned int> m_indices = {0, 1, 2};
    void createMesh();
    void drawMesh();

};