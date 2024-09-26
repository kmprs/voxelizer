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
              -.25f, -.25f, -.25f,  1.f, 0.f, 0.f,
              -.25f,  .25f, -.25f,  1.f, 0.f, 0.f,
               .25f, -.25f, -.25f,  1.f, 0.f, 0.f,
               .25f,  .25f, -.25f,  1.f, 0.f, 0.f,
              -.25f, -.25f,  .25f, -1.f, 0.f, 0.f,
              -.25f,  .25f,  .25f, -1.f, 0.f, 0.f,
               .25f, -.25f,  .25f, -1.f, 0.f, 0.f,
               .25f,  .25f,  .25f, -1.f, 0.f, 0.f,
    };
    std::vector<unsigned int> m_indices = {0, 1, 2,
                                           1, 3, 2,
                                           4, 5, 6,
                                           5, 7, 6};
    void createMesh();
    void drawMesh();

};