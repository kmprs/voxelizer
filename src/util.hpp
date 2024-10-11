#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <glm/vec3.hpp>
#include "octreeNode.hpp"
#include "triangleFace.hpp"
#include "voxel.hpp"


namespace util
{
    [[nodiscard]] std::vector<std::string> split( const std::string &s, char delimiter );
    [[nodiscard]] float findMax( const std::vector<glm::vec3> &input );
    bool differentSign( float test, float a, float b );
    bool doIntervalsIntersect( const std::array<float, 2> &interval0,
                               const std::array<float, 2> &interval1 );

    [[nodiscard]] std::array<Triangle, 12>
    getCubeTriangles( const glm::vec3 &positions, float edgeLength );

    namespace octree
    {
        void findleavesAtMaxDepth( OctreeNode* node, int depth, int &maxDepth,
                                   std::vector<OctreeNode*> &leaves );

        std::vector<Voxel> toVoxel( OctreeNode* node, int depth );
    }

    namespace voxel
    {
        Voxel
        createVoxel( const glm::vec3 &position, unsigned int offset, float edgeLength );
    }
}