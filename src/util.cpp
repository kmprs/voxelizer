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
        for ( const glm::vec3 &vec : input)
        {
            maximum = std::max( { maximum, vec.x, vec.y, vec.z });
        }
        return maximum;
    }

    void findleavesAtMaxDepth( OctreeNode* node, int depth, int& maxDepth, std::vector<OctreeNode*>& leaves )
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
}