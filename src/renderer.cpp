#include "renderer.hpp"

extern unsigned int programID;

Renderer::Renderer()
{
    createMesh();
}

void Renderer::render()
{
    glClearColor( 0.35f, 0.4f, 0.37f, 1.0f );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    drawMesh();
}

void Renderer::createMesh()
{
    float* vertices = &m_vertices[0];
    unsigned int* indices = &m_indices[0];

    glGenVertexArrays( 1, &m_VAO );
    glBindVertexArray( m_VAO );

    // Buffer for vertices
    glGenBuffers( 1, &m_VBO );
    glBindBuffer( GL_ARRAY_BUFFER, m_VBO );
    glBufferData( GL_ARRAY_BUFFER, sizeof(float) * m_vertices.size(), vertices, GL_STATIC_DRAW );

    // Vertex attribute pointer for position (location = 0 in vertex shader)
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)nullptr );
    glEnableVertexAttribArray( 0 );

    // Vertex attribute pointer for normals (location = 1 in vertex shader)
    glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)) );
    glEnableVertexAttribArray( 1 );

    // Buffer for indices
    glGenBuffers( 1, &m_EBO );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_EBO );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * m_indices.size(), indices, GL_STATIC_DRAW );
}

void Renderer::drawMesh()
{
    glBindVertexArray( m_VAO );
    glDrawElements( GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, nullptr );
    glBindVertexArray( 0 );
}
