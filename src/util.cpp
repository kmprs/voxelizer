#include "util.hpp"

namespace util
{
    std::vector<std::string> split( const std::string &s, char delimiter )
    {
        std::vector<std::string> tokens;
        std::string token;
        std::istringstream tokenStream( s );
        while ( std::getline( tokenStream, token, delimiter ))
        {
            tokens.push_back( token );
        }
        return tokens;
    }


    float findMax( const std::vector<glm::vec3> &input )
    {
        float maximum = 0.f;
        for ( const glm::vec3 &vec: input )
        {
            maximum = std::max( { maximum, vec.x, vec.y, vec.z } );
        }
        return maximum;
    }

    void findleavesAtMaxDepth( OctreeNode* node, int depth, int &maxDepth,
                               std::vector<OctreeNode*> &leaves )
    {
        if ( node->isLeaf )
        {
            if ( depth > maxDepth )
            {
                maxDepth = depth;
                leaves.clear();
            }
            if ( depth == maxDepth )
            {
                leaves.push_back( node );
            }
        } else
        {
            for ( OctreeNode* child: node->children )
            {
                findleavesAtMaxDepth( child, depth + 1, maxDepth, leaves );
            }
        }
    }

    std::array<Triangle, 12>
    getCubeTriangles( const glm::vec3 &position, float edgeLength )
    {
        float halfLength = edgeLength / 2.0f;

        // Define the 8 vertices of the cube relative to the center
        glm::vec3 v0 = position + glm::vec3( -halfLength, -halfLength, -halfLength );
        glm::vec3 v1 = position + glm::vec3( halfLength, -halfLength, -halfLength );
        glm::vec3 v2 = position + glm::vec3( halfLength, -halfLength, halfLength );
        glm::vec3 v3 = position + glm::vec3( -halfLength, -halfLength, halfLength );
        glm::vec3 v4 = position + glm::vec3( -halfLength, halfLength, -halfLength );
        glm::vec3 v5 = position + glm::vec3( halfLength, halfLength, -halfLength );
        glm::vec3 v6 = position + glm::vec3( halfLength, halfLength, halfLength );
        glm::vec3 v7 = position + glm::vec3( -halfLength, halfLength, halfLength );

        // Create 2 triangles for each face of the cube
        std::array<Triangle, 12> triangles = {
                // Front face
                Triangle( v0, v1, v4 ), Triangle( v1, v5, v4 ),

                // Back face
                Triangle( v3, v2, v7 ), Triangle( v2, v6, v7 ),

                // Left face
                Triangle( v0, v3, v4 ), Triangle( v3, v7, v4 ),

                // Right face
                Triangle( v1, v2, v5 ), Triangle( v2, v6, v5 ),

                // Top face
                Triangle( v4, v5, v7 ), Triangle( v5, v6, v7 ),

                // Bottom face
                Triangle( v0, v1, v3 ), Triangle( v1, v2, v3 )
        };

        return triangles;
    }
}