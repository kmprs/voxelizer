#pragma once

#include <iostream>
#include <vector>
#include "GL/glew.h"
#include "types.hpp"


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

    std::vector<float> m_vertices = {
            -.25f, -.25f, -.25f,  1.f, 0.f, 0.f,
            -.25f,  .25f, -.25f,  1.f, 0.f, 0.f,
            .25f, -.25f, -.25f,  1.f, 0.f, 0.f,
            .25f,  .25f, -.25f,  1.f, 0.f, 0.f,

            -.25f, -.25f,  .25f, -1.f, 0.f, 0.f,
            -.25f,  .25f,  .25f, -1.f, 0.f, 0.f,
            .25f, -.25f,  .25f, -1.f, 0.f, 0.f,
            .25f,  .25f,  .25f, -1.f, 0.f, 0.f,

            -.25f, -.25f,  .25f,  0.f, 1.f, 0.f,
            -.25f, -.25f, -.25f,  0.f, 1.f, 0.f,
            .25f, -.25f,  .25f,  0.f, 1.f, 0.f,
            .25f, -.25f, -.25f,  0.f, 1.f, 0.f,

            -.25f, .25f, -.25f,  0.f, -1.f, 0.f,
            -.25f, .25f,  .25f,  0.f, -1.f, 0.f,
            .25f, .25f, -.25f,  0.f, -1.f, 0.f,
            .25f, .25f,  .25f,  0.f, -1.f, 0.f,

            -.25f, -.25f,  .25f,  0.f, 0.f, 1.f,
            -.25f, -.25f, -.25f,  0.f, 0.f, 1.f,
            -.25f,  .25f,  .25f,  0.f, 0.f, 1.f,
            -.25f,  .25f, -.25f,  0.f, 0.f, 1.f,

            .25f, -.25f, -.25f,  0.f, 0.f, -1.f,
            .25f, -.25f,  .25f,  0.f, 0.f, -1.f,
            .25f,  .25f, -.25f,  0.f, 0.f, -1.f,
            .25f,  .25f,  .25f,  0.f, 0.f, -1.f,
    };
    std::vector<unsigned int> m_indices =
            {
                    0, 1, 2,
                    1, 3, 2,

                    4, 5, 6,
                    5, 7, 6,

                    8, 9,  10,
                    9, 11, 10,

                    12, 13, 14,
                    13, 15, 14,

                    16, 17, 18,
                    17, 19, 18,

                    20, 21, 22,
                    21, 23, 22,

            };
};