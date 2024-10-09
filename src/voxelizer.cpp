#include "voxelizer.hpp"
#include "util.hpp"


Voxelizer::Voxelizer( const std::vector<std::shared_ptr<TriangleFace>> &triangleFaces )
{
    for ( const std::shared_ptr<TriangleFace> &triangleFace: triangleFaces )
    {
        m_meshTriangles.push_back( triangleFace->toTriangle());
    }
}


void Voxelizer::buildOctree( OctreeNode* node, int depth, int maxDepth )
{

    if ( depth >= maxDepth ) return;
    std::cout << "I'm here" << std::endl;
    // fetch vertex positions from octree node
    std::array<Triangle, 12> voxelTriangles = util::getCubeTriangles( node->position,
                                                                      node->edgeLength );


    bool found = false;
    for ( const Triangle &voxelTriangle: voxelTriangles )
    {
        for ( const Triangle &meshTriangle: m_meshTriangles )
        {
            // check for triangle-triangle intersection
            if ( doTrianglesIntersect( meshTriangle, voxelTriangle ))
            {
                node->isAir = false;
                // new function call of buildOctree with children of node
                if ( depth - 1 < maxDepth )
                {
                    node->createChildren();
                    for ( OctreeNode* child: node->children )
                    {
                        buildOctree( child, depth + 1, maxDepth );
                    }
                }
                found = true;
                break;
            }
        }
        if ( found ) break;
    }
}

Voxel Voxelizer::createVoxel( const glm::vec3 &position, unsigned int offset,
                              float edgeLength )
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


bool Voxelizer::doTrianglesIntersect( const Triangle &t1, const Triangle &t2 )
{
    // TODO implement algorithm
    return true;
}
