#include "renderer.hpp"

extern unsigned int programID;

Renderer::Renderer()
{
    std::shared_ptr<Voxel> v1 = std::make_shared<Voxel>( createVoxel( { .5f, .5f, 0.f }, 0, 0.5f ));
    std::shared_ptr<Voxel> v2 = std::make_shared<Voxel>( createVoxel( { 0.f, 0.f, 0.f }, 24, 0.5f ));
    m_renderables.push_back( v1 );
    m_renderables.push_back( v2 );
    m_mesh = Mesh( m_renderables );
}

void Renderer::render()
{
    glClearColor( 0.35f, 0.4f, 0.37f, 1.0f );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    m_mesh.draw();
}


Voxel Renderer::createVoxel( const glm::vec3 &position, unsigned int offset, float size )
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


