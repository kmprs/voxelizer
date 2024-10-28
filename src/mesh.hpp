#pragma once

#include <vector>
#include <glm/vec3.hpp>
#include "GL/glew.h"
#include "renderable.hpp"


class Mesh
{
public:
    Mesh( const std::vector<std::shared_ptr<Renderable>>& renderables);
    Mesh() = default;
    ~Mesh() = default;

    void draw();

private:
    GLuint m_VAO = 0;
    GLuint m_VBO = 0;
    GLuint m_EBO = 0;

    std::vector<float> m_vertices = {};
    std::vector<unsigned int> m_indices = {};

    void createData( const std::vector<std::shared_ptr<Renderable>> &objects );

};