#pragma once

#include <vector>
#include <glm/vec3.hpp>
#include "voxel.hpp"
#include "triangleFace.hpp"
#include "octreeNode.hpp"
#include "util.hpp"
#include "constants.hpp"

class OctreeVoxelizer
{
public:
    OctreeVoxelizer() = default;

    std::vector<Voxel> run(const std::vector<std::shared_ptr<TriangleFace>> triangleFaces);
    void
    buildOctree( OctreeNode* node, int depth, int maxDepth,
                 std::vector<BVHNode*> &leaves, long &counter );

private:
    std::vector<std::shared_ptr<TriangleFace>> m_meshTriangles = {};
    static bool doTrianglesIntersect( const Triangle &t0, const Triangle &t1 );
    static float
    computePlaneDistance( const glm::vec3 &normal, const glm::vec3 &point,
                          float distance );
    static std::array<float, 2>
    computeTriangleLineInterval( const Triangle &triangle,
                                 const glm::vec3 &intersectionDirection,
                                 const std::array<float, 3> &distances );
    static float
    projectOntoAxis( const glm::vec3 &distance, const glm::vec3 &trianglePoint );
};


