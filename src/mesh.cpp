#include "mesh.hpp"

Mesh::Mesh( const std::vector<std::shared_ptr<Renderable>> &renderables )
{
    createData( renderables );

    float* vertices = &m_vertices[0];
    unsigned int* indices = &m_indices[0];

    glGenVertexArrays( 1, &m_VAO );
    glBindVertexArray( m_VAO );

    // Buffer for m_vertices
    glGenBuffers( 1, &m_VBO );
    glBindBuffer( GL_ARRAY_BUFFER, m_VBO );
    glBufferData( GL_ARRAY_BUFFER, sizeof( float ) * m_vertices.size(), vertices,
                  GL_STATIC_DRAW );

    // Vertex attribute pointer for position (location = 0 in vertex shader)
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof( float ),
                           ( void* ) nullptr );
    glEnableVertexAttribArray( 0 );

    // Vertex attribute pointer for normals (location = 1 in vertex shader)
    glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof( float ),
                           ( void* ) ( 3 * sizeof( float )));
    glEnableVertexAttribArray( 1 );

    // Buffer for m_indices
    glGenBuffers( 1, &m_EBO );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_EBO );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( unsigned int ) * m_indices.size(),
                  indices, GL_STATIC_DRAW );
}

void Mesh::draw()
{
    glBindVertexArray( m_VAO );
    glDrawElements( GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, nullptr );
    glBindVertexArray( 0 );
}


void Mesh::createData( const std::vector<std::shared_ptr<Renderable>> &objects )
{
    for ( const std::shared_ptr<Renderable> &object: objects )
    {
        std::vector<float> vertexData = object->getVertexData();
        std::vector<unsigned int> indices = object->getIndices();
        m_vertices.insert( m_vertices.end(), vertexData.begin(), vertexData.end());
        m_indices.insert( m_indices.end(), indices.begin(), indices.end());
    }
}


