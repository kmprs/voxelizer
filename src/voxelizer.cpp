#include "voxelizer.hpp"

std::vector<std::shared_ptr<Voxel>>
Voxelizer::convert( const std::vector<std::shared_ptr<TriangleFace>> &triangleFaces)
{
    std::vector<std::shared_ptr<Voxel>> result;

    for ( int i = 0; i < triangleFaces.size()-1; i++)
    {
        Voxel v = createVoxel({i, 0, 0}, i * 24, i / 2);
        result.push_back(std::make_shared<Voxel>(v));
    }

    return result;
}

Voxel Voxelizer::createVoxel( const glm::vec3 &position, unsigned int offset,
                              float edgeLength ) const
{
    float halfLength = edgeLength / 2.0f;

    glm::vec3 normals[6] = {
            { 0,  0,  1 },  // Front
            { 0,  0,  -1 },  // Back
            { 0,  1,  0 },  // Top
            { 0,  -1, 0 },  // Bottom
            { -1, 0,  0 },  // Left
            { 1,  0,  0 }   // Right
    };

    Vertex frontVertices[4] = {
            { position.x - halfLength, position.y - halfLength, position.z + halfLength,
                    normals[0].x, normals[0].y, normals[0].z },
            { position.x + halfLength, position.y - halfLength, position.z + halfLength,
                    normals[0].x, normals[0].y, normals[0].z },
            { position.x - halfLength, position.y + halfLength, position.z + halfLength,
                    normals[0].x, normals[0].y, normals[0].z },
            { position.x + halfLength, position.y + halfLength, position.z + halfLength,
                    normals[0].x, normals[0].y, normals[0].z }
    };

    Vertex backVertices[4] = {
            { position.x + halfLength, position.y - halfLength, position.z - halfLength,
                    normals[1].x, normals[1].y, normals[1].z },
            { position.x - halfLength, position.y - halfLength, position.z - halfLength,
                    normals[1].x, normals[1].y, normals[1].z },
            { position.x + halfLength, position.y + halfLength, position.z - halfLength,
                    normals[1].x, normals[1].y, normals[1].z },
            { position.x - halfLength, position.y + halfLength, position.z - halfLength,
                    normals[1].x, normals[1].y, normals[1].z }
    };


    Vertex topVertices[4] = {
            { position.x - halfLength, position.y + halfLength, position.z + halfLength,
                    normals[2].x, normals[2].y, normals[2].z },
            { position.x + halfLength, position.y + halfLength, position.z + halfLength,
                    normals[2].x, normals[2].y, normals[2].z },
            { position.x - halfLength, position.y + halfLength, position.z - halfLength,
                    normals[2].x, normals[2].y, normals[2].z },
            { position.x + halfLength, position.y + halfLength, position.z - halfLength,
                    normals[2].x, normals[2].y, normals[2].z }
    };

    Vertex bottomVertices[4] = {
            { position.x - halfLength, position.y - halfLength, position.z - halfLength,
                    normals[3].x, normals[3].y, normals[3].z },
            { position.x + halfLength, position.y - halfLength, position.z - halfLength,
                    normals[3].x, normals[3].y, normals[3].z },
            { position.x - halfLength, position.y - halfLength, position.z + halfLength,
                    normals[3].x, normals[3].y, normals[3].z },
            { position.x + halfLength, position.y - halfLength, position.z + halfLength,
                    normals[3].x, normals[3].y, normals[3].z }
    };

    Vertex leftVertices[4] = {
            { position.x - halfLength, position.y - halfLength, position.z - halfLength,
                    normals[4].x, normals[4].y, normals[4].z },
            { position.x - halfLength, position.y - halfLength, position.z + halfLength,
                    normals[4].x, normals[4].y, normals[4].z },
            { position.x - halfLength, position.y + halfLength, position.z - halfLength,
                    normals[4].x, normals[4].y, normals[4].z },
            { position.x - halfLength, position.y + halfLength, position.z + halfLength,
                    normals[4].x, normals[4].y, normals[4].z }
    };


    Vertex rightVertices[4] = {
            { position.x + halfLength, position.y - halfLength, position.z + halfLength,
                    normals[5].x, normals[5].y, normals[5].z },
            { position.x + halfLength, position.y - halfLength, position.z - halfLength,
                    normals[5].x, normals[5].y, normals[5].z },
            { position.x + halfLength, position.y + halfLength, position.z + halfLength,
                    normals[5].x, normals[5].y, normals[5].z },
            { position.x + halfLength, position.y + halfLength, position.z - halfLength,
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
