#include "mesh.hpp"

Mesh::Mesh()
{
    std::unique_ptr<RenderableObject> voxel1 = std::make_unique<Voxel>( createVoxel( { .5f, .5f, 0 }, 24, .5f ));
    std::unique_ptr<RenderableObject> voxel2 = std::make_unique<Voxel>( createVoxel( { 0, 0, 0 }, 0, .5f ));
    std::vector<std::unique_ptr<RenderableObject>> objects;
    objects.push_back( std::move( voxel1 ));
    objects.push_back( std::move( voxel2 ));

    Vertex vertices2[3] = {
            Vertex( -10.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f ),
            Vertex( -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f ),
            Vertex( 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f )
    };

    std::unique_ptr<TriangleFace> t2 = std::make_unique<TriangleFace>( vertices2, 48 );
    objects.push_back( std::move( t2 ));
    createData( objects );

    float* vertices = &m_vertices[0];
    unsigned int* indices = &m_indices[0];

    glGenVertexArrays( 1, &m_VAO );
    glBindVertexArray( m_VAO );

    // Buffer for vertices
    glGenBuffers( 1, &m_VBO );
    glBindBuffer( GL_ARRAY_BUFFER, m_VBO );
    glBufferData( GL_ARRAY_BUFFER, sizeof( float ) * m_vertices.size(), vertices, GL_STATIC_DRAW );

    // Vertex attribute pointer for position (location = 0 in vertex shader)
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof( float ), ( void* ) nullptr );
    glEnableVertexAttribArray( 0 );

    // Vertex attribute pointer for normals (location = 1 in vertex shader)
    glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof( float ), ( void* ) ( 3 * sizeof( float )));
    glEnableVertexAttribArray( 1 );

    // Buffer for indices
    glGenBuffers( 1, &m_EBO );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_EBO );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( unsigned int ) * m_indices.size(), indices, GL_STATIC_DRAW );
}

void Mesh::draw()
{
    glBindVertexArray( m_VAO );
    glDrawElements( GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, nullptr );
    glBindVertexArray( 0 );
}


void Mesh::createData( const std::vector<std::unique_ptr<RenderableObject>> &objects )
{
    for ( const std::unique_ptr<RenderableObject> &object: objects )
    {
        std::vector<float> vertexData = object->getVertexData();
        std::vector<unsigned int> indices = object->getIndices();
        m_vertices.insert( m_vertices.end(), vertexData.begin(), vertexData.end());
        m_indices.insert( m_indices.end(), indices.begin(), indices.end());
    }
}


Voxel Mesh::createVoxel( const glm::vec3 &position, unsigned int offset, float size )
{
    float halfSize = size / 2.0f;

    glm::vec3 normals[6] = {
            { 0,  0,  1 },  // Front
            { 0,  0,  -1 }, // Back
            { 0,  1,  0 },  // Top
            { 0,  -1, 0 }, // Bottom
            { -1, 0,  0 }, // Left
            { 1,  0,  0 }   // Right
    };

    Vertex frontVertices[4] = {
            { position.x - halfSize, position.y - halfSize, position.z + halfSize,
                    normals[0].x, normals[0].y, normals[0].z },
            { position.x + halfSize, position.y - halfSize, position.z + halfSize,
                    normals[0].x, normals[0].y, normals[0].z },
            { position.x - halfSize, position.y + halfSize, position.z + halfSize,
                    normals[0].x, normals[0].y, normals[0].z },
            { position.x + halfSize, position.y + halfSize, position.z + halfSize,
                    normals[0].x, normals[0].y, normals[0].z }
    };

    Vertex backVertices[4] = {
            { position.x + halfSize, position.y - halfSize, position.z - halfSize,
                    normals[1].x, normals[1].y, normals[1].z },
            { position.x - halfSize, position.y - halfSize, position.z - halfSize,
                    normals[1].x, normals[1].y, normals[1].z },
            { position.x + halfSize, position.y + halfSize, position.z - halfSize,
                    normals[1].x, normals[1].y, normals[1].z },
            { position.x - halfSize, position.y + halfSize, position.z - halfSize,
                    normals[1].x, normals[1].y, normals[1].z }
    };


    Vertex topVertices[4] = {
            { position.x - halfSize, position.y + halfSize, position.z + halfSize,
                    normals[2].x, normals[2].y, normals[2].z },
            { position.x + halfSize, position.y + halfSize, position.z + halfSize,
                    normals[2].x, normals[2].y, normals[2].z },
            { position.x - halfSize, position.y + halfSize, position.z - halfSize,
                    normals[2].x, normals[2].y, normals[2].z },
            { position.x + halfSize, position.y + halfSize, position.z - halfSize,
                    normals[2].x, normals[2].y, normals[2].z }
    };

    Vertex bottomVertices[4] = {
            { position.x - halfSize, position.y - halfSize, position.z - halfSize,
                    normals[3].x, normals[3].y, normals[3].z },
            { position.x + halfSize, position.y - halfSize, position.z - halfSize,
                    normals[3].x, normals[3].y, normals[3].z },
            { position.x - halfSize, position.y - halfSize, position.z + halfSize,
                    normals[3].x, normals[3].y, normals[3].z },
            { position.x + halfSize, position.y - halfSize, position.z + halfSize,
                    normals[3].x, normals[3].y, normals[3].z }
    };

    Vertex leftVertices[4] = {
            { position.x - halfSize, position.y - halfSize, position.z - halfSize,
                    normals[4].x, normals[4].y, normals[4].z },
            { position.x - halfSize, position.y - halfSize, position.z + halfSize,
                    normals[4].x, normals[4].y, normals[4].z },
            { position.x - halfSize, position.y + halfSize, position.z - halfSize,
                    normals[4].x, normals[4].y, normals[4].z },
            { position.x - halfSize, position.y + halfSize, position.z + halfSize,
                    normals[4].x, normals[4].y, normals[4].z }
    };


    Vertex rightVertices[4] = {
            { position.x + halfSize, position.y - halfSize, position.z + halfSize,
                    normals[5].x, normals[5].y, normals[5].z },
            { position.x + halfSize, position.y - halfSize, position.z - halfSize,
                    normals[5].x, normals[5].y, normals[5].z },
            { position.x + halfSize, position.y + halfSize, position.z + halfSize,
                    normals[5].x, normals[5].y, normals[5].z },
            { position.x + halfSize, position.y + halfSize, position.z - halfSize,
                    normals[5].x, normals[5].y, normals[5].z }
    };

    // Create voxel faces with calculated vertices and the provided offset
    VoxelFace frontFace( frontVertices, offset + 0 );
    VoxelFace backFace( backVertices, offset + 4 );
    VoxelFace topFace( topVertices, offset + 8 );
    VoxelFace bottomFace( bottomVertices, offset + 12 );
    VoxelFace leftFace( leftVertices, offset + 16 );
    VoxelFace rightFace( rightVertices, offset + 20 );

    // Create and return the voxel
    return { frontFace, backFace, topFace, bottomFace, leftFace, rightFace };
}


