#pragma once

#include <glm/vec3.hpp>
#include "GL/glew.h"
#include "voxel.hpp"
#include "triangleFace.hpp"


class Mesh
{
public:
    Mesh();
    ~Mesh() = default;

    void draw();

private:
    GLuint m_VAO = 0;
    GLuint m_VBO = 0;
    GLuint m_EBO = 0;

    std::vector<float> m_vertices = {};
    std::vector<unsigned int> m_indices = {};

    void createData( const std::vector<std::unique_ptr<RenderableObject>> &objects );
    Voxel createVoxel(const glm::vec3 &position, unsigned int offset, float size);
};