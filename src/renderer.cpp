#include "renderer.hpp"
#include "dataHandler.hpp"

extern unsigned int programID;

Renderer::Renderer()
{
    std::unique_ptr<DataHandler> dataHandler = std::make_unique<DataHandler>( MODEL_PATH, OBJ );
    std::vector<std::shared_ptr<TriangleFace>> triangleFaces = dataHandler->getTriangleFaces();
    m_renderables.insert( m_renderables.end(), triangleFaces.begin(), triangleFaces.end());

    Voxel v = createVoxel({0, 0, 0}, m_renderables.size() * 3, 2);
    m_renderables.push_back(std::make_shared<Voxel>(v));
    m_mesh = Mesh( m_renderables );


}

void Renderer::render()
{
    glClearColor( BACKGROUND_COLOR.x, BACKGROUND_COLOR.y, BACKGROUND_COLOR.z, 1.f );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    m_mesh.draw();
}


Voxel Renderer::createVoxel( const glm::vec3 &position, unsigned int offset, float edgeLength )
{
    float halfSize = edgeLength / 2.0f;

    glm::vec3 normals[6] = {
            { 0,  0,  1 },  // Front
            { 0,  0,  -1 },  // Back
            { 0,  1,  0 },  // Top
            { 0,  -1, 0 },  // Bottom
            { -1, 0,  0 },  // Left
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


