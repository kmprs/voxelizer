#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <glm/vec3.hpp>
#include "octreeNode.hpp"
#include "voxel.hpp"
#include "triangleFace.hpp"


namespace util
{
    [[nodiscard]] std::vector<std::string> split( const std::string &s, char delimiter );
    [[nodiscard]] float findMax( const std::vector<glm::vec3> &input );
    bool differentSign( float test, float a, float b );
    bool doIntervalsIntersect( const std::array<float, 2> &interval0,
                               const std::array<float, 2> &interval1 );


    namespace geometry
    {
        [[nodiscard]] std::array<Triangle, 12>
        getCubeTriangles( const glm::vec3 &positions, float edgeLength );
        std::vector<glm::vec3>
        extractPositions( const std::vector<std::shared_ptr<TriangleFace>> &triangleFaces );
        glm::vec3 minVec( const std::vector<glm::vec3> &vectors );
        glm::vec3 maxVec( const std::vector<glm::vec3> &vectors );
        bool doBoundingVolumesIntersect( const glm::vec3 &min1, const glm::vec3 &max1,
                                         const glm::vec3 &min2, const glm::vec3 &max2 );
    }

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

    namespace bvh
    {
        void createChildren( BVHNode* node, int depth, int maxDepth );
        void getLeaves( BVHNode* node, std::vector<BVHNode*> &leaves);
    }
}